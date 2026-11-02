#pragma once

/*** @public ***/

#define STR(x) #x
#define XSTR(x) STR(x)

#define LINE_AS_STRING XSTR(__LINE__)

#define panic(message) \
    do { _panic(message, __FILE__, LINE_AS_STRING, __func__); } while (0)

#define kassert(stmt, message) \
    do { if (!(stmt)) {panic(message);} } while (0)
