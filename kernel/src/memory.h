#pragma once

#include <stddef.h>

void *memcpy(void *restrict dest, const void *restrict src, usize n);
void *memset(void *s, int c, usize n);
void *memmove(void *dest, const void *src, usize n);
int memcmp(const void *s1, const void *s2, usize n);

// Make uses of these functions go through the compiler builtins, which the
// compiler can optimise (e.g. inline) even when building freestanding code,
// falling back to calling the implementations in memory.c otherwise.
#define memcpy __builtin_memcpy
#define memset __builtin_memset
#define memmove __builtin_memmove
#define memcmp __builtin_memcmp
