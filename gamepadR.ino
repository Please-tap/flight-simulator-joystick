/*
 * Example of working 2 Thumbsticks (PS2 Thumbstick for Arduino) with Calibration
 * Connect first thumbstick X to A1, Y to A0
 *         second thumbstick X to A3,Y to A2
 */
//including a library
#include <Gamepad.h>

//initialize a centers of axises for calibration
int rightXcenter = 500;
int rightYcenter = 500;
int leftXcenter = 500;
int leftYcenter = 500;
double multiplierRX = 0.254; //127 / 500
double multiplierRY = 0.254;
double multiplierLX = 0.254;
double multiplierLY = 0.254;

//Initializing a Gamepad
Gamepad gp;
bool buttonState = 0;  
const int buttonPin = A5; 

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  //attachInterrupt(digitalPinToInterrupt(buttonPin), blink, CHANGE);
  //attachInterrupt(buttonPin, blink, CHANGE);
  //initializing inputs
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  Serial.print(12);
  calibrate();
}

void loop() {
  if (buttonState != digitalRead(buttonPin)) {
    buttonState = !buttonState;
    gp.setButtonState(8, !buttonState);
  }
  //buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);
  int rx, ry;
  rx = analogRead(A1);
  ry = analogRead(A0);
  //we need to convert a 0-1000 to -127 - 127
  rx = floor((rx - rightXcenter) * multiplierRX);
  ry = floor((ry - rightYcenter) * multiplierRY);
  if(rx > 127) rx = 127;
  if(ry > 127) ry = 127;
  gp.setRightXaxis(-rx);
  //gp.setButtonState(8, 1);
  //because i have placed a thumbstick in breadboard, i must invert a Y axis and swap X and Y axises
  gp.setRightYaxis(ry);
  delay(20);
}



void blink() {
   buttonState = digitalRead(buttonPin);
   gp.setButtonState(8, !buttonState);
}


void calibrate()
{
  int rx, ry;
  int i = 0;
  while(i < 8)
  {
    rx = analogRead(A1);
    ry = analogRead(A0);
    bool validRX = rx > (rightXcenter - 100) && rx < (rightXcenter + 100);
    bool validRY = ry > (rightYcenter - 100) && ry < (rightYcenter + 100);
    if(validRX && validRY)
    {
      i++;
      //nothing to do here!
    }
    else i = 0;
    delay(20);
  }
  rightXcenter = rx;
  rightYcenter = ry;
  multiplierRX = (double)127 / (double)rx;
  multiplierRY = (double)127 / (double)ry;
}
