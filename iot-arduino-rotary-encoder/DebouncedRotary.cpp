#include "DebouncedRotary.h"

#include "Utils.h"

DebouncedRotary::DebouncedRotary(int _pinA, int _pinB, int _debounceUs)
{
    pinA = _pinA;
    pinB = _pinB;
    debounceUs = _debounceUs;
}

void DebouncedRotary::ISRHandler()
{
    int stateA = digitalRead(pinA);
    int stateB = digitalRead(pinB);
    unsigned long u = micros();

    if (stateA == HIGH && pressed) // signal HIGH
    {
        if (releasing)
        {
            if (timeDiff(u, releasedBegin) >= debounceUs)
            {
                pressed = releasing = false;
            }
        }
        else
        {
            releasing = true;
            releasedBegin = u;
        }
    }
    else // signal LOW
    {
        if (releasing)
        {
            if (timeDiff(u, releasedBegin) >= debounceUs)
            {
                pressed = releasing = false;
            }
        }

        if (pressed)
        {
            releasing = false;
        }
        else
        {
            pressed = true;
            pressedBegin = u;

            if (stateA == HIGH)
            {
                if (stateB == LOW)
                    ++rotPos;
                else
                    --rotPos;
            }
            else
            {
                if (stateB == HIGH)
                    ++rotPos;
                else
                    --rotPos;
            }
        }
    }
}

int DebouncedRotary::getRotPos() const
{
    return rotPos;
}