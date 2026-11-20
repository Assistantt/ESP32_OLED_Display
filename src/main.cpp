#include <Arduino.h>
#include <Wire.h>
#include "oled_driver.h"

#define I2C_SDA 23
#define I2C_SCL 22
#define MAX_I2C_ADRESS 127

void setup() {
    Serial.begin(115200);

    Wire.begin(I2C_SDA, I2C_SCL);
    Wire.beginTransmission(0x3C);
Wire.write(0x00); // Наступні байти — команди

Wire.write(0xAE); // Display OFF
Wire.write(0x8D); // Charge pump
Wire.write(0x14); // Enable charge pump
Wire.write(0xA8); // Multiplex ratio
Wire.write(0x3F); // 64 рядки
Wire.write(0xD3); // Display offset
Wire.write(0x00);
Wire.write(0x40); // Display start line = 0
Wire.write(0xA1); // Segment remap
Wire.write(0xC8); // COM scan direction
Wire.write(0xDA); // COM pins
Wire.write(0x12);
Wire.write(0xA6); // Normal display
Wire.write(0xA5); // Увімкнути всі пікселі незалежно від RAM
Wire.write(0xAF); // Display ON

uint8_t error = Wire.endTransmission();

Serial.printf("OLED command status: %u\n", error);
    Serial.println("I2C Scanner started");

    uint8_t found_devices = 0;
    for(uint8_t counter = 1; counter < MAX_I2C_ADRESS; counter++){
        Wire.beginTransmission(counter);

        uint8_t error = Wire.endTransmission();

        if(error == 0){
            Serial.print("Device found at address: 0x");

            if (counter < 16){
                Serial.print("0");
            }

            Serial.println(counter, HEX);

            found_devices++;
        }
    }
    Serial.print("Total devices found: ");
    Serial.println(found_devices);

    oledClearBuffer();
    oledDrawPixel(64, 32, true);
    oledUpdate();
}

void loop() {
}
