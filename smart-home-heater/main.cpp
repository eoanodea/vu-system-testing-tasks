#include "mbed.h"
#include "board_freedom.h"
#include <cstdio>
 
  //smart-home
// main() runs in its own thread in the OS
int main()
{

    board_init();
 
 
    DigitalOut Fan (PTC12);
    DigitalOut Curtain (PTE24);

    char temp;


    Curtain = 1;

    pwm3.write(0.5); //heater on
    pwm3.period_ms(10);
    Fan = 1;



    // printf("HEY Temperature is  %d \n\t", temp);


    
    // unsigned int pwm_min=580;
 
    while (true)
    {
        // printf(ADC0_SE16);
        temp = (ADC0_SE16);

        printf("Temperature is  %d \n\t", temp);
        ThisThread::sleep_for(1000ms);
        // if (Car_Sensor == 0) {
        //     ThisThread::sleep_for(1s);
        //     Garage_Door = 1;
        // ThisThread::sleep_for(5s);
            // Garage_Door = 0; 
        // }
    }
 
   
}
