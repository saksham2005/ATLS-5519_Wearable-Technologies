/**************************************************************************************************************************************************************************************

Title:      Magic Lapel Flower
Designer:   Saksham Sabharwal
Date:       01 May 2017

Design References:  1) Mario the Magician's Magical Lapel Flower - https://learn.sparkfun.com/tutorials/mario-the-magicians-magical-lapel-flower
                    2) SIK Experiment Guide for Arduino - Flex Sensor - https://learn.sparkfun.com/tutorials/sik-experiment-guide-for-arduino---v32/experiment-9-using-a-flex-sensor
                     
**************************************************************************************************************************************************************************************/

/* Header files */
#include <Servo.h> 

/* Global variable declarations */
Servo servo1;
const int flexpin = 0; 

void setup() 
{ 
  Serial.begin(9600);
  servo1.attach(10);
} 

void loop() 
{ 
  int flexposition;    // Input value from the analog pin.
  int servoposition;   // Output value to the servo.

  flexposition = analogRead(flexpin);   // Read the position of the flex sensor (0 to 1023):

  // Because the voltage divider circuit only returns a portion
  // of the 0-1023 range of analogRead(), we'll map() that range
  // to the servo's range of 0 to 180 degrees. The flex sensors
  // we use are usually in the 600-900 range:

  servoposition = map(flexposition, 720, 930, 180, 0);
  servoposition = constrain(servoposition, 0, 180);
  servo1.write(servoposition);    // Move servo to that position

  // Because every flex sensor has a slightly different resistance,
  // the 600-900 range may not exactly cover the flex sensor's
  // output. To help tune our program, we'll use the serial port to
  // print out our values to the serial monitor window:

  Serial.print("sensor: ");
  Serial.print(flexposition);
  Serial.print("  servo: ");
  Serial.println(servoposition);
  delay(20);  // wait 20ms between servo updates
}
