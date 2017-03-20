/**********************************************************************************************************************************

Title:      Interactive Badges - Display messages on an 7x8 LED matrix using Arduino powered Sparkfun Redstick
Designer:   Saksham Sabharwal
Date:       16 March 2017

Design References:  1) LED Array Hookup Tutorials - https://learn.sparkfun.com/tutorials/sparkfun-led-array-8x7-hookup-guide
                    2) Sparkfun Device Listing - https://www.sparkfun.com/products/13795
                    3) Charlieplexing Library - https://code.google.com/archive/p/yacll/
                    4) LED Array Library - https://github.com/sparkfun/SparkFun_LED_Array_8x7_Arduino_Library/archive/master.zip

***********************************************************************************************************************************/

/* Header files */
#include <SparkFun_LED_8x7.h>
#include <Chaplex.h>

/* Variable declarations */
static byte led_pins[] = {0, 1, 2, 3, 4, 5, 6, 7}; // Pins for LEDs

void setup()
{
  Plex.init(led_pins);    // Initialize LED array
  Plex.clear();           // Clear display
  Plex.display();
}

void loop()
{
  Plex.scrollText("you suck", 1);   // Scroll text once
  delay(4000);                      // Wait 4 seconds to allow for scrolling
  Plex.stopScrolling();             // Stop scrolling the text
  delay(1000);
}
