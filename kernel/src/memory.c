#include <memory.h>

// GCC and Clang reserve the right to generate calls to the following
// 4 functions even if they are not directly called.
// They must be implemented as the C specification mandates.
// DO NOT remove or rename these functions, or stuff will eventually break!

#ifdef memcpy
#  undef memcpy
#endif
public void *memcpy(void *restrict dest, const void *restrict src, usize n) {
    u8 *pdest = dest;
    const u8 *psrc = src;

    for (usize i = 0; i < n; i++) {
        pdest[i] = psrc[i];
    }

    return dest;
}

#ifdef memset
#  undef memset
#endif
public void *memset(void *s, int c, usize n) {
    u8 *p = s;

    for (usize i = 0; i < n; i++) {
        p[i] = (u8)c;
    }

    return s;
}

#ifdef memmove
#  undef memmove
#endif
public void *memmove(void *dest, const void *src, usize n) {
    u8 *pdest = dest;
    const u8 *psrc = src;

    if ((uptr)src > (uptr)dest) {
        for (usize i = 0; i < n; i++) {
            pdest[i] = psrc[i];
        }
    } else if ((uptr)src < (uptr)dest) {
        for (usize i = n; i > 0; i--) {
            pdest[i-1] = psrc[i-1];
        }
    }

    return dest;
}

#ifdef memcmp
#  undef memcmp
#endif
public int memcmp(const void *s1, const void *s2, usize n) {
    const u8 *p1 = s1;
    const u8 *p2 = s2;

    for (usize i = 0; i < n; i++) {
        if (p1[i] != p2[i]) {
            return p1[i] < p2[i] ? -1 : 1;
        }
    }

    return 0;
}
