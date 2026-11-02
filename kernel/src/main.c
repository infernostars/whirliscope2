#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <limine.h>

#include "error.h"
#include "format.h"
#include "serial.h"

// Set the base revision to 6, this is recommended as this is the latest
// base revision described by the Limine boot protocol specification.
// See specification for further info.

in_section(".limine_requests") static volatile u64 limine_base_revision[] = LIMINE_BASE_REVISION(6);

// The Limine requests can be placed anywhere, but it is important that
// the compiler does not optimise them away, so, usually, they should
// be made volatile or equivalent, _and_ they should be accessed at least
// once or marked as used with the "used" attribute as done here.

in_section(".limine_requests") static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST_ID,
    .revision = 0
};

// Finally, define the start and end markers for the Limine requests.
// These can also be moved anywhere, to any .c file, as seen fit.

in_section(".limine_requests_start") static volatile u64 limine_requests_start_marker[] = LIMINE_REQUESTS_START_MARKER;

in_section(".limine_requests_end") static volatile u64 limine_requests_end_marker[] = LIMINE_REQUESTS_END_MARKER;


// Scale an 8-bit colour channel value to the size the framebuffer gives the
// channel and move it into place within a pixel.
static u32 fb_channel(u8 value, u8 mask_size, u8 mask_shift) {
    u64 max = ((u64)1 << mask_size) - 1;
    return (u32)((value * max / 255) << mask_shift);
}

// Build a pixel from 8-bit red, green and blue values following the channel
// layout of the framebuffer.
static u32 fb_pixel(struct limine_framebuffer *fb, u8 red, u8 green, u8 blue) {
    return fb_channel(red, fb->red_mask_size, fb->red_mask_shift)
         | fb_channel(green, fb->green_mask_size, fb->green_mask_shift)
         | fb_channel(blue, fb->blue_mask_size, fb->blue_mask_shift);
}

// Print a nice pattern to a framebuffer as an example.
static void fb_pattern(struct limine_framebuffer *fb) {
    volatile u32 *fb_ptr = fb->address;
    for (usize y = 0; y < fb->height; y++) {
        for (usize x = 0; x < fb->width; x++) {
            u8 nX = x % 256;
            u8 nY = y % 256;
            fb_ptr[y * (fb->pitch / 4) + x] = fb_pixel(fb, 0, nY, nX);
        }
    }
}

noreturn void kmain(void) {
    bool serial_succeeded = init_serial();
    kassert(serial_succeeded, "serial failed to initialize"); // Technically, if serial fails, we might now be able to write to output but... whatever
    write_serial_string("Yay! Yippee! Hooray!\n\n");

    kassert(LIMINE_BASE_REVISION_SUPPORTED(limine_base_revision), "limine revision not supported");

    kassert(framebuffer_request.response != NULL, "wtf no framebuffer");
    kassert(framebuffer_request.response->framebuffer_count >= 1, "wtf less than 1 framebuffers");

    // You will see my cool ass pattern.
    for (u64 i = 0; i < framebuffer_request.response->framebuffer_count; i++) {
        struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[i];

        kassert(framebuffer->memory_model == LIMINE_FRAMEBUFFER_RGB && framebuffer->bpp == 32, "invalid framebuffer model");

        fb_pattern(framebuffer);
    }

    char* v = format_u64(0x1234567890abcdef,  (char*) __builtin_alloca(sizeof(char) * 19));

    write_serial_string(v);

    __asm__("ud2");

    // Ok time to die
    kassert(false, "nothing to do");
}
