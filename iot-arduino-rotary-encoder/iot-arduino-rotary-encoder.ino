#include <limits.h>

// INT0 available on pin 2
#define ENCODER_PIN_A 2
// INT1 available on pin 3
#define ENCODER_PIN_BTN 3
#define ENCODER_PIN_B 4

#define DEBOUNCE_ROT_US 1500
#define DEBOUNCE_BTN_MS 50

unsigned long timeDiff(unsigned long now, unsigned long start)
{
    if (start <= now)
        return now - start;
    else
        return (ULONG_MAX - start) + now + 1;
}

bool encoderRotAPressed = true;
long encoderRotAPressedBegin = 0;
bool encoderRotAReleasing = false;
long encoderRotAReleasedBegin = 0;
volatile int encoderRotPos = 0;

// encoder A signal change
void ISR_encoderA()
{
    int stateA = digitalRead(ENCODER_PIN_A);
    int stateB = digitalRead(ENCODER_PIN_B);

    if (stateA == HIGH && encoderRotAPressed) // signal HIGH
    {
        if (encoderRotAReleasing)
        {
            if (timeDiff(micros(), encoderRotAReleasedBegin) >= DEBOUNCE_ROT_US)
            {
                encoderRotAPressed = false;
                encoderRotAReleasing = false;
            }
        }
        else
        {
            encoderRotAReleasing = true;
            encoderRotAReleasedBegin = micros();
        }
    }
    else // signal LOW
    {
        if (encoderRotAReleasing)
        {
            if (timeDiff(micros(), encoderRotAReleasedBegin) >= DEBOUNCE_ROT_US)
            {
                encoderRotAPressed = false;
                encoderRotAReleasing = false;
            }
        }

        if (encoderRotAPressed)
        {
            encoderRotAReleasing = false;
        }
        else
        {
            encoderRotAPressed = true;
            encoderRotAPressedBegin = millis();

            if (stateA == HIGH)
            {
                if (stateB == LOW)
                    ++encoderRotPos;
                else
                    --encoderRotPos;
            }
            else
            {
                if (stateB == HIGH)
                    ++encoderRotPos;
                else
                    --encoderRotPos;
            }
        }
    }
}

bool encoderBtnPressed = true;
long encoderBtnPressedBegin = 0;
bool encoderBtnReleasing = false;
long encoderBtnReleasedBegin = 0;
volatile int encoderBtnPressCount = 0;

// encoder btn signal change
void ISR_encoderBtn()
{
    int state = digitalRead(ENCODER_PIN_BTN);

    if (state == HIGH && encoderBtnPressed) // signal HIGH
    {
        if (encoderBtnReleasing)
        {
            if (timeDiff(millis(), encoderBtnReleasedBegin) >= DEBOUNCE_BTN_MS)
            {
                encoderBtnPressed = false;
                encoderBtnReleasing = false;
            }
        }
        else
        {
            encoderBtnReleasing = true;
            encoderBtnReleasedBegin = millis();
        }
    }
    else // signal LOW
    {
        if (encoderBtnReleasing)
        {
            if (timeDiff(millis(), encoderBtnReleasedBegin) >= DEBOUNCE_BTN_MS)
            {
                encoderBtnPressed = false;
                encoderBtnReleasing = false;
            }
        }

        if (encoderBtnPressed)
        {
            encoderBtnReleasing = false;
        }
        else
        {
            encoderBtnPressed = true;
            encoderBtnPressedBegin = millis();
            ++encoderBtnPressCount;
        }
    }
}

int btnCnt = -1;
int rotPos = -1;

void setup()
{
    Serial.begin(115200);

    pinMode(ENCODER_PIN_A, INPUT_PULLUP);
    pinMode(ENCODER_PIN_B, INPUT_PULLUP);
    pinMode(ENCODER_PIN_BTN, INPUT_PULLUP);

    attachInterrupt(0, ISR_encoderA, CHANGE);
    attachInterrupt(1, ISR_encoderBtn, CHANGE);
}

void loop()
{
    if (btnCnt != encoderBtnPressCount)
    {
        btnCnt = encoderBtnPressCount;
        Serial.print("btn pressed cnt:");
        Serial.println(btnCnt);
    }

    if (rotPos != encoderRotPos)
    {
        rotPos = encoderRotPos;
        Serial.print("encoder rot pos:");
        Serial.println(rotPos);
    }
}
