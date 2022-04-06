#include "mbed.h"

// main() runs in its own thread in the OS
int main()
{
    DigitalOut signalOut(PTC12);

    signalOut = 0;

    while (true) {
        signalOut = 1;
        wait_us(100);

        

        signalOut = 0;
        wait_us(900);
    }
}

