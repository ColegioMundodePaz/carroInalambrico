/* JoyStick module transceiver code
 - CONNECTIONS: nRF24L01 Modules See:
   1 - GND
   2 - VCC 3.3V !!! NOT 5V
   3 - CE to Arduino pin 9
   4 - CSN to Arduino pin 10
   5 - SCK to Arduino pin 13
   6 - MOSI to Arduino pin 11
   7 - MISO to Arduino pin 12
   8 - UNUSED
   
   Default Button Pins: 
   A - pin 2
   B - pin 3
   C - pin 4
   D - pin 5
   - 
   Analog Joystick module
   GND    to Arduino GND
   VCC    to Arduino +5V
   X Pot  to Arduino A0
   Y Pot  to Arduino A1
/*-----( Import needed libraries )-----*/

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

#define CE_PIN   9
#define CSN_PIN 10
#define xAxis 14     // A0 for Arduino UNO
#define yAxis 15     // A1 for Arduino UNO

// NOTE: the "LL" at the end of the constant is "LongLong" type
const uint64_t pipe = 0xE8E8F0F0E1LL; // Define the transmit pipe

/*-----( Declare objects )-----*/
RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

/*-----( Declare Variables )-----*/
int joystick[10];  // 6 element array holding Joystick reading and 4 buttons
int button_A = 2;
int button_B = 3;
int button_C = 4;
int button_D = 5;
int button_E = 6;
int button_F = 7;
int button_K = 8;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipe);
  radio.stopListening();
  
  //declare pinMode for all buttons and initial state
  pinMode(button_A,INPUT_PULLUP);
  pinMode(button_B,INPUT_PULLUP);
  pinMode(button_C,INPUT_PULLUP);
  pinMode(button_D,INPUT_PULLUP);
  pinMode(button_E,INPUT_PULLUP);
  pinMode(button_F,INPUT_PULLUP);
  pinMode(button_K,INPUT_PULLUP);  
  digitalWrite(button_A,LOW);
  digitalWrite(button_B,LOW);
  digitalWrite(button_C,LOW);
  digitalWrite(button_D,LOW);
  digitalWrite(button_E,LOW);
  digitalWrite(button_F,LOW);
  digitalWrite(button_K,LOW);
}

void loop() {  
  joystick[0] = analogRead(xAxis);
  joystick[1] = analogRead(yAxis);
  joystick[2] = digitalRead(button_A);
  joystick[3] = digitalRead(button_B);
  joystick[4] = digitalRead(button_C);
  joystick[5] = digitalRead(button_D);
  joystick[6] = digitalRead(button_E);
  joystick[7] = digitalRead(button_F);
  joystick[8] = digitalRead(button_K);  
  radio.write( joystick, sizeof(joystick) );

  delay(20);
  Serial.print("X = ");
  Serial.print(map(analogRead(xAxis), 0, 690, 0, 255));
  Serial.print(" Y = ");  
  Serial.print(map(analogRead(yAxis), 0, 690, 0, 255));
  Serial.print(" A = "); 
  Serial.print(digitalRead(button_A));
  Serial.print(" B = "); 
  Serial.print(digitalRead(button_B));
  Serial.print(" C = "); 
  Serial.print(digitalRead(button_C));
  Serial.print(" D = "); 
  Serial.print(digitalRead(button_D));
  Serial.print(" E = "); 
  Serial.print(digitalRead(button_E));
  Serial.print(" F = "); 
  Serial.print(digitalRead(button_F));
  Serial.print(" K = "); 
  Serial.println(digitalRead(button_K));
}