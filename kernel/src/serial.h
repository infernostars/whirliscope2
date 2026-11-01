#pragma once

#include <stdbool.h>
#include <stdint.h>

bool init_serial();

bool serial_received();
u8 read_serial();

bool is_transmit_empty();
void write_serial(u8 a);
void write_serial_string(const char* a);
