/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/home/ianp/Documents/iot2021/labs/lab-13/src/lab-13.ino"
#include "oled-wing-adafruit.h"

void setup();
void loop();
void isr();
#line 3 "/home/ianp/Documents/iot2021/labs/lab-13/src/lab-13.ino"
SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(MANUAL);
OledWingAdafruit display;

volatile bool interruptOccured = false; //must be declared volatile if used inside an isr.
int count = 0;                          //must be declared volatile if used inside an isr.

bool noInterrupt = false;

void setup()
{
    pinMode(D6, INPUT_PULLUP);
    pinMode(D7, INPUT);

    attachInterrupt(D6, isr, FALLING); // D6 will now generate an interrupt on the falling edge and will run the code in the isr

    display.setup();
    display.clearDisplay();
    display.display();
}

void loop()
{
    if (interruptOccured)
    {
        count = count + 1;
        interruptOccured = false;
    }

    if (digitalRead(D7))
    {
        if (noInterrupt)
        {
            interrupts();
        }
        else
        {
            noInterrupts();
        }

        noInterrupt = !noInterrupt;
        delay(500);
    }

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);

    display.printlnf("count: %d", count);
    display.display();
}

void isr()
{
    // your interrupt handler code here
    interruptOccured = true;
}