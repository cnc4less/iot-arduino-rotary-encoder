#ifndef _CONFIG_H
#define _CONFIG_H

//----------------------------------------------------------------------------
// rotary encoder
//----------------------------------------------------------------------------
#define ENCODER_A_PIN PD2
#define ENCODER_P_PIN PD3
#define ENCODER_B_PIN PD4

#ifdef ARDUINO_ARCH_STM32
#define ENCODER_A_INT digitalPinToInterrupt(ENCODER_A_PIN)
#define ENCODER_P_INT digitalPinToInterrupt(ENCODER_P_PIN)
#else
#define ENCODER_A_INT 0
#define ENCODER_P_INT 1
#endif

//----------------------------------------------------------------------------
// 16x2 LCD
//----------------------------------------------------------------------------
// uncomment follow to enable I2C device address scan
//#define I2C_DEVICE_SCAN
#define LCD_ADDR 0x3f
#define LCD_COLS 16
#define LCD_ROWS 2
#define LCD_SDA_PIN PB9
#define LCD_SCL_PIN PB8

#endif
