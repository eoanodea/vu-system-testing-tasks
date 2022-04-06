#include "mbed.h"

// main() runs in its own thread in the OS
int main()
{
    DigitalOut redLed(PTC12);

    redLed = 0;

    while (true) {
        redLed = 1;
        // redLed = !redLed;
        // ThisThread::sleep_for(500ms);
    }
}

