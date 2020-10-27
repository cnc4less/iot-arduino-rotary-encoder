#include "LCD.h"

#include <Arduino.h>

LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);

#ifdef I2C_DEVICE_SCAN
void scan_twi_loop()
{
    byte error, address;
    int Devices;
    Serial.println("Scanning...");
    Devices = 0;
    for (address = 1; address < 127; address++)
    {

        Wire.beginTransmission(address);
        error = Wire.endTransmission();
        if (error == 0)
        {
            Serial.print("I2C device found at address 0x");
            if (address < 16)
                Serial.print("0");
            Serial.print(address, HEX);
            Serial.println("  !");
            Devices++;
        }
        else if (error == 4)
        {
            Serial.print("Unknown error at address 0x");
            if (address < 16)
                Serial.print("0");
            Serial.println(address, HEX);
        }
    }
    if (Devices == 0)
        Serial.println("No I2C devices found\n");
    else
        Serial.println("done\n");
    delay(5000);
}
#endif

void init_lcd()
{
    // ref: https://github.com/stm32duino/Arduino_Core_STM32/blob/master/libraries/Wire/examples/i2c_scanner/i2c_scanner.ino
    Serial.println("init lcd");
    #ifdef ARDUINO_ARCH_STM32
    Wire.setSDA(LCD_SDA_PIN);
    Wire.setSCL(LCD_SCL_PIN);
    #endif
    Wire.begin();

    lcd.init();
    lcd.init();
    lcd.backlight();
    lcd.clear();
}
