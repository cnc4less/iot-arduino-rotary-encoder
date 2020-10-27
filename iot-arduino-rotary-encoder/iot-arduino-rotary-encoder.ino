#include "config.h"

#include <Arduino.h>

#include "LCD.h"
#include "DebouncedRotary.h"
#include "DebouncedButton.h"

// forward method
void update_lcd();

// rotary AB handle

DebouncedRotary rotaryAB(ENCODER_A_PIN, ENCODER_B_PIN);

void ISR_encoderA()
{
    rotaryAB.ISRHandler();
}

int rotaryPosPrev = 0;
void handleRotA()
{
    int rotaryPos = rotaryAB.getRotPos();

    if (rotaryPos != rotaryPosPrev)
    {
        if (rotaryPos > rotaryPosPrev)
        {
            // some stuf on CCW rotary
        }
        else
        {
            // some stuff on CW rotary
        }

        rotaryPosPrev = rotaryPos;

        update_lcd();
    }
}

// rotary P handle

DebouncedButton rotaryP(ENCODER_P_PIN);

void ISR_encoderP()
{
    rotaryP.ISRHandler();
}

int rotaryPPressCountPrev = 0;
void handleRotP()
{
    if (rotaryP.getPressCount() != rotaryPPressCountPrev)
    {
        rotaryPPressCountPrev = rotaryP.getPressCount();

        update_lcd();
    }
}

// update lcd

void update_lcd()
{    
    lcd.setCursor(0, 0);
    String s = String("rotPos:") + String(rotaryPosPrev);    
    lcd.print(s);
    int slen = s.length();
    if (slen < LCD_COLS)
    {
        for (int i=0; i < LCD_COLS-slen; ++i) lcd.print(" ");
    }

    lcd.setCursor(0, 1);
    lcd.print("rotClk:");
    lcd.print(rotaryPPressCountPrev);
}

// setup

void setup()
{
    Serial.begin(115200);

    init_lcd();
    update_lcd();

    pinMode(ENCODER_A_PIN, INPUT_PULLUP);
    pinMode(ENCODER_B_PIN, INPUT_PULLUP);
    pinMode(ENCODER_P_PIN, INPUT_PULLUP);

    attachInterrupt(ENCODER_A_INT, ISR_encoderA, CHANGE);
    attachInterrupt(ENCODER_P_INT, ISR_encoderP, CHANGE);
}

// main loop

void loop()
{
#ifdef I2C_DEVICE_SCAN
    scan_twi_loop();
    return;
#endif

    handleRotA();
    handleRotP();
}
