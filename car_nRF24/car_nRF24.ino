/* JoyStick module receiver code
 - CONNECTIONS: nRF24L01 Modules See:
   1 - GND
   2 - VCC 3.3V !!! NOT 5V
   3 - CE to Arduino pin 6
   4 - CSN to Arduino pin 8
   5 - SCK to Arduino pin 13
   6 - MOSI to Arduino pin 11
   7 - MISO to Arduino pin 12
   8 - UNUSED
 */
//-----( Import needed libraries )-----
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
/*-----( Declare Constants and Pin Numbers )-----*/
#define CE_PIN 6
#define CSN_PIN 8

// NOTE: the "LL" at the end of the constant is "LongLong" type
const uint64_t pipe = 0xE8E8F0F0E1LL; // Define the transmit pipe

#define IN_1  2          // L298N #1 in 1 motor Front Right
#define IN_2  3          // L298N #1 in 2 motor Front Right
#define IN_3  4          // L298N #1 in 3 motor Back Right
#define IN_4  5          // L298N #1 in 4 motor Back Right



/*-----( Declare objects )-----*/
RF24 radio(CE_PIN, CSN_PIN); // Create a Radio
/*-----( Declare Variables )-----*/
int joystick[6];  // 6 element array holding Joystick readings
int speedRight = 0;
int speedLeft = 0;
int  xAxis, yAxis;
// the four button variables from joystick
int button_A;
int button_B;
int button_C;
int button_D;

void setup()
{
    

  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);
    


  Serial.begin(9600);
  Serial.println("Nrf24L01 Receiver Starting"); 
  
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();
}

void loop()
{
  if ( radio.available() )
  {
      radio.read( joystick, sizeof(joystick) );
      xAxis = joystick[0];
      yAxis = joystick[1];
      
      // the four button variables from joystick array
      int button_A = joystick[2];
      int button_B = joystick[3];
      int button_C = joystick[4];
      int button_D = joystick[5];
  

// Y-axis used for forward and backward control
    if (yAxis < 340) {
    // Set Right Motors backward
    digitalWrite(IN_1, HIGH);
    digitalWrite(IN_2, LOW);
    digitalWrite(IN_3, HIGH);
    digitalWrite(IN_4, LOW);
  }

else if (yAxis > 350) {
    // Set Right Motors forward
    digitalWrite(IN_1, LOW);
    digitalWrite(IN_2, HIGH);
    digitalWrite(IN_3, LOW);
    digitalWrite(IN_4, HIGH);
  }
  else {
    digitalWrite(IN_1, LOW);
    digitalWrite(IN_2, LOW);
    digitalWrite(IN_3, LOW);
    digitalWrite(IN_4, LOW);
  }

// X-axis used for left and right control
  if (xAxis < 340) {
    digitalWrite(IN_1, LOW);
    digitalWrite(IN_2, HIGH);
    digitalWrite(IN_3, LOW);
    digitalWrite(IN_4, LOW);
  }
  if (xAxis > 350) {
    digitalWrite(IN_1, LOW);
    digitalWrite(IN_2, LOW);
    digitalWrite(IN_3, LOW);
    digitalWrite(IN_4, HIGH);
  }
  // Prevent buzzing at low speeds (Adjust according to your motors. My motors couldn't start moving if PWM value was below value of 70)
  if (speedLeft < 70) {
    speedLeft = 0;
  }
  if (speedRight < 70) {
    speedRight = 0;
  }


     
      Serial.print("X = ");
      Serial.print(xAxis);
      Serial.print(" Y = ");  
      Serial.print(yAxis);
      Serial.print(" A = ");
      Serial.print(joystick[2]);
      Serial.print(" B = ");  
      Serial.print(joystick[3]);
      Serial.print(" C = ");
      Serial.print(joystick[4]);
      Serial.print(" D = ");  
      Serial.println(joystick[5]);
      
      
      
      }

    

  
      
  }













  