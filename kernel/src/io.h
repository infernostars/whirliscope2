#pragma once

#include <stdint.h>

static inline u8 inb(u16 port)
{
    u8 ret;
    __asm__ volatile ( "inb %w1, %b0"
                   : "=a"(ret)
                   : "Nd"(port)
                   : "memory");
    return ret;
}

static inline u16 inw(u16 port)
{
    u16 ret;
    __asm__ volatile ( "inw %w1, %w0"
                   : "=a"(ret)
                   : "Nd"(port)
                   : "memory");
    return ret;
}

static inline u32 inl(u16 port)
{
    u32 ret;
    __asm__ volatile ( "inl %w1, %k0"
                   : "=a"(ret)
                   : "Nd"(port)
                   : "memory");
    return ret;
}

static inline void outb(u16 port, u8 val)
{
    __asm__ volatile ( "outb %b0, %w1" : : "a"(val), "Nd"(port) : "memory");
}

static inline void outw(u16 port, u16 val)
{
    __asm__ volatile ( "outw %w0, %w1" : : "a"(val), "Nd"(port) : "memory");
}


static inline void outl(u16 port, u32 val) {
    __asm__ volatile ( "outl %k0, %w1" : : "a"(val), "Nd"(port) : "memory");
}
