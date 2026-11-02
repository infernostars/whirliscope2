#pragma once

/*** @public ***/

// Make uses of these functions go through the compiler builtins, which the
// compiler can optimise (e.g. inline) even when building freestanding code,
// falling back to calling the implementations in memory.c otherwise.
#define memcpy __builtin_memcpy
#define memset __builtin_memset
#define memmove __builtin_memmove
#define memcmp __builtin_memcmp
