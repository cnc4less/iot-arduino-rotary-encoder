#ifndef _DEBOUNCED_ROTARY_H
#define _DEBOUNCED_ROTARY_H

#include <Arduino.h>

/**
 * Prerequisites:
 * - pinMode(ROT_A_PIN, INPUT_PULLUP);
 * - pinMode(ROT_A_PIN, INPUT_PULLUP);
 * - attachInterrupt(digitalPinToInterrupt(ROT_A_PIN), fwdISR, CHANGE);
 * - void fwdISR() { debouncedRotaryAB.ISRHandler(); }
 * Check change by comparing debouncedBRotaryAB.getRotPos()
 */
class DebouncedRotary
{
    int pinA, pinB;
    int debounceUs;

    bool pressed = true;
    unsigned long pressedBegin = 0;
    bool releasing = false;
    unsigned long releasedBegin = 0;

    volatile int rotPos = 0;
public:
    DebouncedRotary(int _pinA, int _pinB, int _debounceUs = 1500);

    void ISRHandler();    
    int getRotPos() const;
};

#endif