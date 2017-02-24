/**********************************************************************************************************************************

Title:      Program to control and display messages on an 8x8 LED matrix using Arduino Pro Micro
Designer:   Saksham Sabharwal
Date:       16 February 2017

Design References:  1) Brainy Bits Tutorials - https://brainy-bits.com/blogs/tutorials/scroll-text-using-the-max7219-led-dot-matrix
                    2) Sparkfun Device Listing - https://www.sparkfun.com/products/11861
                    3) Arduino Tutorials - https://www.arduino.cc/en/Tutorial/StateChangeDetection

***********************************************************************************************************************************/

/* Variable declarations */
unsigned char i,j;
int button = 3;              // Button
int buttonPushCounter = 0;   // Counter for the number of button presses
int buttonState = 0;         // Current state of the button
int lastButtonState = 0;     // Previous state of the button

/*Port Definitions*/
int Max7219_pinDIN = 7;
int Max7219_pinCS = 8;
int Max7219_pinCLK = 9;

/* Message Display Arrays */

// Display 1 = GO BUFFS
unsigned char disp1[8][8]={
  {0x3C,0x40,0x40,0x40,0x40,0x4C,0x44,0x3C},  //G
  {0x3C,0x42,0x42,0x42,0x42,0x42,0x42,0x3C},  //O
  {0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},          //Blank
  {0x3C,0x22,0x22,0x3E,0x22,0x22,0x3C,0x0},   //B
  {0x42,0x42,0x42,0x42,0x42,0x42,0x22,0x1C},  //U
  {0x7C,0x40,0x40,0x7C,0x40,0x40,0x40,0x40},  //F
  {0x3E,0x20,0x20,0x3E,0x20,0x20,0x20,0x20},  //F
  {0x0,0x1E,0x20,0x20,0x3E,0x2,0x2,0x3C},     //S
};

// Display 2 = THE RISE
unsigned char disp2[8][8]={
  {0x0,0x3E,0x8,0x8,0x8,0x8,0x8,0x8},         //T
  {0x44,0x44,0x44,0x7C,0x44,0x44,0x44,0x44},  //H
  {0x7C,0x40,0x40,0x7C,0x40,0x40,0x40,0x7C},  //E
  {0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},          //Blank
  {0x3C,0x22,0x22,0x22,0x3C,0x24,0x22,0x21},  //R
  {0x7C,0x10,0x10,0x10,0x10,0x10,0x10,0x7C},  //I
  {0x0,0x1E,0x20,0x20,0x3E,0x2,0x2,0x3C},     //S
  {0x7C,0x40,0x40,0x7C,0x40,0x40,0x40,0x7C},  //E
};

/* Function to write an entire byte to the LED Matrix */
void Write_Max7219_byte(unsigned char DATA) 
{   
  unsigned char i;                          // Local traversal variable
  digitalWrite(Max7219_pinCS,LOW);    
  for(i=8;i>=1;i--)
  {     
    digitalWrite(Max7219_pinCLK,LOW);
    digitalWrite(Max7219_pinDIN,DATA&0x80); // Extracting a bit data
    DATA = DATA<<1;
    digitalWrite(Max7219_pinCLK,HIGH);
  }                                 
}

/* Function to write to the LED Matrix */
void Write_Max7219(unsigned char address,unsigned char dat)
{
  digitalWrite(Max7219_pinCS,LOW);
  Write_Max7219_byte(address);           // Address code of LED
  Write_Max7219_byte(dat);               // Data figure on LED 
  digitalWrite(Max7219_pinCS,HIGH);
}

/* Function to initialize the LED Matrix */
void Init_MAX7219(void)
{
  Write_Max7219(0x09, 0x00);       // Decoding BCD
  Write_Max7219(0x0a, 0x03);       // Brightness 
  Write_Max7219(0x0b, 0x07);       // Scanlimit 8 LEDs
  Write_Max7219(0x0c, 0x01);       // Power-down mode0 normal mode 1
  Write_Max7219(0x0f, 0x00);       // Test display 1 EOT display 0
}

void setup()
{
  pinMode(button, INPUT);          // Set the button for reading
  pinMode(Max7219_pinCLK,OUTPUT);
  pinMode(Max7219_pinCS,OUTPUT);
  pinMode(Max7219_pinDIN,OUTPUT);
  delay(50);
  Init_MAX7219();
}

void loop()
{ 
  buttonState = digitalRead(button); // Binary on/off read
  if (buttonState != lastButtonState)
  {
    if (buttonState == HIGH)
      buttonPushCounter++;
    delay(50);
  }
  lastButtonState=buttonState;
  if (buttonPushCounter % 2 == 0)
  {
    for(j=0;j<8;j++)
      {
      for(i=1;i<9;i++)
        Write_Max7219(i,disp2[j][i-1]);
      delay(500);
      }
  }
  else
  {
    for(j=0;j<8;j++)
    {
      for(i=1;i<9;i++)
        Write_Max7219(i,disp1[j][i-1]);
      delay(500);
    }
  }
}
