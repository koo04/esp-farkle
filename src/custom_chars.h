#ifndef CUSTOM_CHARS_H
#define CUSTOM_CHARS_H
#include <cstdint>

uint8_t upArrow[8] = {
    0b00100,
    0b01110,
    0b11111,
    0b00100,
    0b00100,
    0b00100,
    0b00100,
    0b00100
};

uint8_t downArrow[8] = {
    0b00100,
    0b00100,
    0b00100,
    0b00100,
    0b00100,
    0b11111,
    0b01110,
    0b00100
};

uint8_t lock[8] = {
    0b00000,
    0b01110,
    0b10001,
    0b10001,
    0b11111,
    0b11011,
    0b11011,
    0b11111
};

uint8_t bust[8] = {
    0b00000,
    0b00100,
    0b01010,
    0b10101,
    0b01110,
    0b10101,
    0b01010,
    0b00100
};

#endif
