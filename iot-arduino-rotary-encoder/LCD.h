#ifndef _LCD_H
#define _LCD_H

#include "config.h"

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

extern LiquidCrystal_I2C lcd;

#ifdef I2C_DEVICE_SCAN
void scan_twi_loop();
#endif

void init_lcd();

#endif