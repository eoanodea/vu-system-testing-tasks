
//        Sensors
//
//           2 
//      1 --   -- 3 
// 0 --             -- 4

//this program will drive the robot forwards for five seconds
#include "mbed.h"
#include "physcom.h"
using namespace physcom;

Serial pc(USBTX, USBRX); // open a serial communication to terminal emulator
AnalogIn passive_light(p20);

M3pi robot; //create an object of type  M3pi
Ping Pinger(p5); // pin11 for ultrasound connection

// using the lights
DigitalOut redled(p18);


int main() {
   float light_value;
   int range;
   pc.printf("Starting ultrasound \n");
 
   pc.printf("Start calibration!\r\n");
   robot.sensor_auto_calibrate();   //robot executes calibration
   pc.printf("Finished calibration!\r\n");

   wait (2) ;              // wait two seconds
  
//  robot.activate_motor (0, 0.2) ; // drive left motor 1/10 max (  * multiplier) forward
//  robot.activate_motor (1, 0.2) ; // drive right motor 1/10 max (speed * multiplier) forward
     
   while (1) {
        
       /*
         Ultra sound range check
      */
        // check for obstacle
       Pinger.Send();  
       wait_ms(20);

       range = Pinger.Read_cm();
       pc.printf("read centimeters %d\n", range);
      
      while (range < 30 && range > 0) {
              pc.printf("read centimeters %d\n", range);
              robot.activate_motor(0, 0);
              robot.activate_motor(1, 0);
              Pinger.Send();  
              wait_ms(20); 
              range = Pinger.Read_cm();
      }
      
      robot.activate_motor (0, 0.2) ; // drive left motor 1/10 max (speed * multiplier) forward
      robot.activate_motor (1, 0.2) ; // drive right motor 1/10 max (speed * multiplier) forward
     
    
      // for controlling the lights
      light_value = passive_light.read();
      pc.printf("read light %f \n", light_value);

      while (light_value > 0.4) {
         // turn on the lights
         redled = 1;
         light_value = passive_light.read();
         wait_ms(10);
      } 
      redled = 0;

       int sensors[5];
       robot.calibrated_sensors(sensors);  //5 values are read in a vector 
        //pc.printf("sensor values: %d; %d; %d; %d; %d;\r\n", sensors[0], sensors[1],sensors[2], sensors[3], sensors[4]);
       
        // move to the highest value:

        // if the most left sensor is the highest, make a sharp turn (including reverse)
        if ((sensors[0] > sensors[1]) && (sensors[0] > sensors[2]) && (sensors[0] > sensors[3]) && (sensors[0] > sensors[4])) {
           robot.activate_motor(0, -0.2);
           wait_ms(60);
           robot.activate_motor(0, 0.2);  
        }

        // if the second left sensor is the highest, make a smooth turn
        else if ((sensors[1] > sensors[0]) && (sensors[1] > sensors[2]) && (sensors[1] > sensors[3]) && (sensors[1] > sensors[4])) {
           robot.activate_motor (0,0);
           wait_ms(20);
           robot.activate_motor (0, 0.2);
        }

        // if the second right sensor is the highest, make a smooth turn
        else if ((sensors[3] > sensors[0]) && (sensors[3] > sensors[2]) && (sensors[3] > sensors[0]) && (sensors[3] > sensors[4])) {
           robot.activate_motor (1, 0);
           wait_ms(20);
           robot.activate_motor (1, 0.2); 
        }

        // if the most right sensor is the highest, make a sharp turn
        else if ((sensors[4] > sensors[0]) && (sensors[4] > sensors[2]) && (sensors[4] > sensors[1]) && (sensors[4] > sensors[3])) {
           robot.activate_motor (1, -0.2);
           wait_ms(60);
           robot.activate_motor (1,  0.2);
        } 

        // stop neville
        else if ((sensors[2]) < 100) {
           wait_ms(20);
           if ((sensors[1]< 100) && (sensors[3] < 100)) {
              robot.activate_motor (0, 0);
              robot.activate_motor (1, 0);
              break;
           }
        }
    }
}
