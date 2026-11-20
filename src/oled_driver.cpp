#include "oled_driver.h"
#include <Wire.h>
#include <Arduino.h>

#define OLED_ADDRESS 0x3C
#define OLED_CHUNK_SIZE 32

static uint8_t oled_buffer[OLED_BUFFER_SIZE];

void oledUpdate(void){
    const uint8_t commands[] = {0x20, 0x00, 0x21, 0x00, 0x7F, 0x22, 0x00, 0x07};

    oledSendCommands(commands, sizeof(commands));

    for(uint16_t i = 0; i < OLED_BUFFER_SIZE; i+= OLED_CHUNK_SIZE){
        Wire.beginTransmission(OLED_ADDRESS);

        Wire.write(0x40);
        for(uint8_t j = 0; j < OLED_CHUNK_SIZE; j++){
            Wire.write(oled_buffer[i + j]);
        }
    }
    Wire.endTransmission();
}

void oledSendCommands(const uint8_t *commands, size_t size){
    Wire.beginTransmission(OLED_ADDRESS);
    Wire.write(0x00);
    Wire.write(commands, size);

    Wire.endTransmission();
}

void oledClearBuffer(void)
{
    for (uint16_t i = 0; i < OLED_BUFFER_SIZE; i++)
    {
        oled_buffer[i] = 0x00;
    }
}

void oledDrawPixel(uint8_t x, uint8_t y, bool color)
{
    if(x >= OLED_WIDTH || y >= OLED_HEIGHT) return;

    uint16_t column_pixels = y * 128 / 8 + x;
    uint8_t pixels_bit = y % 8;

    if(color == true){
        oled_buffer[column_pixels] |= (1U << pixels_bit); 
    }
    else{
        oled_buffer[column_pixels] &= ~(1U << pixels_bit);
    }
}

