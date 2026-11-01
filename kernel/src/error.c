#include "error.h"
#include "serial.h"

static void breakpoint() {
    __asm__ __volatile__("nop");
}

noreturn static void hcf() {
    for (;;) {
        __asm__ ("hlt");
    }
}

noreturn void _panic(const char* str, const char* file, const char* line, const char* func) {
    write_serial_string("\n\n---<<< KERNEL PANIC: ");
    write_serial_string(str);
    write_serial_string(" >>>---\n\nfile: ");
    write_serial_string(file);
    write_serial(':');
    write_serial_string(line);
    write_serial_string(", at ");
    write_serial_string(func);
    breakpoint();

    // TODO finish me

    hcf();
}