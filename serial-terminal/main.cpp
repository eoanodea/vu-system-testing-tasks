#include "mbed.h"
#include "board_freedom.h"
#include "adc.h"
#include <cstdio>

// main() runs in its own thread in the OS
int main()
{
    board_init();
    while (true) {
        uint16_t analog_in_value = adc_read(0); 
        int analog_max = adc_read(UINT16_MAX);
        float v_ref = 3;
        float volts = (analog_in_value/analog_max*v_ref);

        // printf(v_ref);
        // printf("max is %d", analog_max);

        // UINT16_MAX
        printf("Analog input is at %5d. In Volts: %5f \n\t", analog_in_value, volts);
        // printf("Ahhooooyyyy");
        ThisThread::sleep_for(1000ms);
    }
}

