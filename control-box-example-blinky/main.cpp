#include "mbed.h"

// main() runs in its own thread in the OS
int main()
{
    DigitalOut redLed(PTB2);
    DigitalOut greenLed(PTB3);
    DigitalIn button(PTB7);

    // DigitalOut swLed(PTD1);
    

    redLed = 0;
    greenLed = 0;
    // swLed = 0;

    while (true) {
        // if(redLed) {
        // greenLed = !greenLed;
        // } else {
        // redLed = !redLed;

        // }
        // swLed = !swLed;
        redLed = !button;

        // greenLed = !greenLed;

        ThisThread::sleep_for(100ms);

    }
}

