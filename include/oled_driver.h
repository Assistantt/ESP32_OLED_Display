#ifndef OLED_DRIVER_H
#define OLED_DRIVER_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define OLED_WIDTH  128
#define OLED_HEIGHT 64
#define OLED_BUFFER_SIZE (OLED_WIDTH * OLED_HEIGHT / 8)

void oledUpdate(void);
void oledSendCommands(const uint8_t *commands, size_t size);
void oledClearBuffer(void);
void oledDrawPixel(uint8_t x, uint8_t y, bool color);

#endif