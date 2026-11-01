//
// Created by whirling on 9/28/26.
//

#define PORT 0x3f8          // COM1

#include "serial.h"
#include "io.h"

bool init_serial() {
    outb(PORT + 1, 0x00);    // Disable all interrupts
    outb(PORT + 3, 0x80);    // Enable DLAB to set baud rate divisor
    outb(PORT + 0, 0x01);    // Set divisor to 1 (lo byte) 115200 baud
    outb(PORT + 1, 0x00);    //                  (hi byte)
    outb(PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
    outb(PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
    outb(PORT + 4, 0x0B);    // IRQs enabled, RTS/DSR set
    outb(PORT + 4, 0x1E);    // Set in loopback mode, test the serial chip
    outb(PORT + 0, 0xAE);    // Test serial chip (send byte 0xAE and check if serial returns same byte)

    // Check if serial is faulty (i.e: not same byte as sent)
    if(inb(PORT + 0) != 0xAE) {
        return false;
    }

    // If serial is not faulty set it in normal operation mode
    // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
    outb(PORT + 4, 0x0F);
    return true;
}

bool serial_received() {
    return inb(PORT + 5) & 1;
}

u8 read_serial() {
    while (serial_received() == 0) {}

    return inb(PORT);
}

bool is_transmit_empty() {
    return inb(PORT + 5) & 0x20;
}

void write_serial(u8 a) {
    while (is_transmit_empty() == 0) {}

    outb(PORT, a);
}

void write_serial_string(const char* a) {
    const char *ptr = a;

    while (*ptr != '\0') {
        write_serial(*ptr);
        ptr++;
    }
}
