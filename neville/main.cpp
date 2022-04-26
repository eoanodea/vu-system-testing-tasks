//this program will drive the robot forwards for five seconds
#include "mbed.h"
#include "physcom.h"
using namespace physcom;

Serial pc(USBTX, USBRX); // open a serial communication to terminal emulator
M3pi robot; //create an object of type  M3pi

int main() {
   pc.printf("Start calibration!\r\n");
   robot.sensor_auto_calibrate();   //robot executes calibration
   pc.printf("Finished calibration!\r\n");

  wait (2) ;              // wait two seconds
  
  robot.activate_motor (0,0.2) ; // drive left motor 1/10 max speed forward
  robot.activate_motor (1,0.2) ; // drive right motor 1/10 max speed forward
     
   while (1) {
       int sensors[5];
       robot.calibrated_sensors(sensors);  //5 values are read in a vector 
       pc.printf("sensor values: %d; %d; %d; %d; %d;\r\n", sensors[0], sensors[1],sensors[2], sensors[3], sensors[4]);
       
       ///////////////////////////////// move to the right/////////////////////////////////////////////////////////////
       // to make a VERY sharp turn
       if ((sensors[0] < 50) && (sensors[4] > 950)) {
           robot.activate_motor (1, -0.1);
           wait_ms(40);
           robot.activate_motor (1,0.2);            
       }
       
       // sharp turn
       else if ((sensors[0] < 100) && (sensors[4] > 900)) {
           robot.activate_motor (1, -0.1);
           wait_ms(20);
           robot.activate_motor (1,0.2);            
       }
       
       // make a sharper turn
       else if (sensors[0] > (sensors[2]*3)) {
           robot.activate_motor (0,0);
           wait_ms(40);
           robot.activate_motor (0,0.2);            
       }
       // smooth turn
       else if (sensors[1] > (sensors[2]*3)) {
           robot.activate_motor (0,0);
           wait_ms(10);
           robot.activate_motor (0,0.2);
       }
       
       /////////////////////////////////// turns to the right ///////////////////////////////
       // to make a VERY sharp turn
       else if (sensors[4] < 50 && sensors[0] > 950) {
           robot.activate_motor (0, -0.1);
           wait_ms(40);
           robot.activate_motor (0,0.2);            
       }
       else if (sensors[4] < 100 && sensors[0] > 900) {
           robot.activate_motor (0, -0.1);
           wait_ms(20);
           robot.activate_motor (0,0.2);            
       }
       
       // make a sharp turn
       else if (sensors[4] > (sensors[2]*3)) {
           robot.activate_motor (1,0);
           wait_ms(40);
           robot.activate_motor (1,0.2);            
       }
       // smooth turn
       else if (sensors[3] > (sensors[2]*3)) {
           robot.activate_motor (1,0);
           wait_ms(10);
           robot.activate_motor (1,0.2);
       }
       
   }
               // drive for five seconds
//  robot.activate_motor (0,0);  // stop left motor
//   robot.activate_motor (1,0); // stop right motor
   }
