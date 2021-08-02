#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "RTClib.h"

Adafruit_PWMServoDriver board1 = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver board2 = Adafruit_PWMServoDriver(0x41);
Adafruit_PWMServoDriver board3 = Adafruit_PWMServoDriver(0x42);

#define SERVOMIN  544   // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  2400  // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50   // Analog servos run at ~50 Hz updates

RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

int hourPrevious;
int hourCurrent;
int minutePrevious;
int minuteCurrent;

int returndig1Previous;
int returndig1Current;
int returndig2;
int returndig3Previous;
int returndig3Current;
int returndig4;

void setup() {  
  
  Serial.begin(9600); 

  /* Servo setup */

  board1.begin();  // Initialize servo ccontrol boards
  board2.begin();  
  board3.begin();  
  board1.setOscillatorFrequency(27000000);
  board2.setOscillatorFrequency(27000000);
  board3.setOscillatorFrequency(27000000);
  board1.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
  board2.setPWMFreq(SERVO_FREQ); 
  board3.setPWMFreq(SERVO_FREQ);
  
  yield();
  
  initialize();

  /* RTC setup */

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
  
    // Comment out the two lines of code once the battery has been replaced and the date & time has been set.
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Sets the RTC to the date & time this sketch was compiled
    // rtc.adjust(DateTime(2021, 7, 1, 14, 30, 0));    // Sets the RTC with an explicit date & time, this line sets to July 1 2021, 13:51
  }

  // To reset the time on a previously configured device, reupload this code to the device with the comments removed, then comment them again to avoid any unnecessary rtc reset.
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // rtc.adjust(DateTime(2021, 7, 1, 14, 30, 0));
} 

void loop() {  
  
  DateTime now = rtc.now();     // Get the time from RTC

  hourCurrent = now.hour();     // The current hour (0 - 23)
  minuteCurrent = now.minute(); // The current minute (0 - 59)

  if (hourCurrent != hourPrevious) {               // Check if the hour has changed
    returndig1Current = hourCurrent / 10;          // Get the 1st digit of the hour
    returndig2 = hourCurrent % 10;                 // Get the 2nd digit of the hour
    if (returndig1Current != returndig1Previous) { // Check to see if the first digit has changed (2nd digit will always change)
      digit1(returndig1Current);                   // Change digit 1 on the clock to a new number
      returndig1Previous = returndig1Current;      // Store the new number
    }
    digit2(returndig2);                            // Change digit 2 on the clock to a new number
    hourPrevious = hourCurrent;                    // Store the new number
  }

  if (minuteCurrent != minutePrevious) {           // Check if the minute has changed
    returndig3Current = minuteCurrent / 10;        // Get the 1st digit of the minute
    returndig4 = minuteCurrent % 10;               // Get the 2nd digit of the minute
    if (returndig3Current != returndig3Previous) { // Check to see if the first digit has changed (2nd digit will always change)
      digit3(returndig3Current);                   // Change digit 3 on the clock to a new number
      returndig3Previous = returndig3Current;      // Store the new number
    }
    digit4(returndig4);                            // Change digit 4 on the clock to a new number
    minutePrevious = minuteCurrent;                // Store the new number
  }

  delay(15000);                                    // Wait 15s to check if time has changed
}

/* Determining the angles in which the servos move at */

int angleToPulse(int ang){
   int pulse1 = map(ang,0, 180, SERVOMIN,SERVOMAX); // Map the angles of 0 to 180 to Servo min and Servo max 
   int pulse2 = int(float(pulse1) / 1000000 * SERVO_FREQ * 4096);
   // Serial.print("Angle: ");Serial.print(ang);
   // Serial.print(" pulse: ");Serial.println(pulse);
   return pulse2;
}

/* Actual clock initialization */

void initialize() {
  DateTime now = rtc.now(); // Get the time from RTC

  hourCurrent = (now.hour(), DEC);     // The current hour (0 - 23)
  minuteCurrent = (now.minute(), DEC); // The current minute (0 - 59)

  // Serial.print(hourCurrent); Serial.print(":"); Serial.println(minuteCurrent);
  
  returndig1Current = hourCurrent / 10;   // get 1st digit of hour
  returndig2 = hourCurrent % 10;          // get 2nd digit of hour
  returndig3Current = minuteCurrent / 10; // get 1st digit of minute
  returndig4 = minuteCurrent % 10;        // get 2nd digit of minute
  
  // Serial.print(returndig1Current); Serial.print(returndig2); Serial.print(returndig3Current); Serial.println(returndig4);

  for (int dig1 = 0; dig1 <= 2; dig1++){                 // Cycle 1st digit from 0-2
    digit1(dig1);
    // Serial.println(dig1);
    delay(100);
  }
  for (int dig1 = 0; dig1 <= returndig1Current; dig1++){ // Cycle 1st digit from 0 to current time 
    digit1(dig1);
    // Serial.println(dig1);
    delay(100);
  }
  
  for (int dig2 = 0; dig2 <= 9; dig2++){                // Cycle 2nd digit from 0-9
    digit2(dig2);
    // Serial.println(dig2);
    delay(100);
  }
  for (int dig2 = 0; dig2 <= returndig2; dig2++){       // Cycle 1st digit from 0 to current time
    digit2(dig2);
    // Serial.println(dig2);
    delay(100);
  }

  for (int dig3 = 0; dig3 <= 5; dig3++){                 // Cycle 3rd digit from 0-5
    digit3(dig3);
    delay(100);
  }
  for (int dig3 = 0; dig3 <= returndig3Current; dig3++){ // Cycle 1st digit from 0 to current time
    digit3(dig3);
    delay(100);
  }

  for (int dig4 = 0; dig4 <= 9; dig4++){                // Cycle 4th digit from 0-9
    digit4(dig4);
    delay(100);
  }
  for (int dig4 = 0; dig4 <= returndig4; dig4++){       // Cycle 1st digit from 0 to current time
    digit4(dig4);
    delay(100);
  }
}

/*The code below are found in the Kinematic clock calibration excel file, under the sheet named "Calibrated digits"

/*1st digit*/

void digit1(int number) {
  if (number == 0) {
    board1.setPWM(5, 0, angleToPulse(72));delay(200);
    board1.setPWM(4, 0, angleToPulse(40));delay(200); 
    board1.setPWM(3, 0, angleToPulse(116));delay(200);
    board1.setPWM(2, 0, angleToPulse(40));delay(200);
    board1.setPWM(1, 0, angleToPulse(119));delay(200);
    board1.setPWM(0, 0, angleToPulse(88));delay(200);
    board1.setPWM(11, 0, angleToPulse(53));delay(200);
    board1.setPWM(10, 0, angleToPulse(8));delay(200);
    board1.setPWM(9, 0, angleToPulse(110));delay(200);
    board1.setPWM(8, 0, angleToPulse(38));delay(200);
    board1.setPWM(7, 0, angleToPulse(120));delay(200);
    board1.setPWM(6, 0, angleToPulse(16));delay(200);
  }
  else if (number == 1) {
    board1.setPWM(5, 0, angleToPulse(16));delay(200);
    board1.setPWM(4, 0, angleToPulse(19));delay(200);
    board1.setPWM(3, 0, angleToPulse(20));delay(200);
    board1.setPWM(2, 0, angleToPulse(19));delay(200);
    board1.setPWM(1, 0, angleToPulse(19));delay(200);
    board1.setPWM(0, 0, angleToPulse(30));delay(200);
    board1.setPWM(11, 0, angleToPulse(52));delay(200);
    board1.setPWM(10, 0, angleToPulse(41));delay(200);
    board1.setPWM(9, 0, angleToPulse(110));delay(200);
    board1.setPWM(8, 0, angleToPulse(38));delay(200);
    board1.setPWM(7, 0, angleToPulse(120));delay(200);
    board1.setPWM(6, 0, angleToPulse(125));delay(200);
  }
  else if (number == 2) {
    board1.setPWM(5, 0, angleToPulse(73));delay(200); 
    board1.setPWM(4, 0, angleToPulse(76));delay(200);
    board1.setPWM(3, 0, angleToPulse(79));delay(200);
    board1.setPWM(2, 0, angleToPulse(39));delay(200);
    board1.setPWM(1, 0, angleToPulse(119));delay(200);
    board1.setPWM(0, 0, angleToPulse(88));delay(200);
    board1.setPWM(11, 0, angleToPulse(53));delay(200); 
    board1.setPWM(10, 0, angleToPulse(8));delay(200);
    board1.setPWM(9, 0, angleToPulse(112));delay(200);
    board1.setPWM(8, 0, angleToPulse(1));delay(200);
    board1.setPWM(7, 0, angleToPulse(15));delay(200);
    board1.setPWM(6, 0, angleToPulse(16));delay(200);
  }
}

/*2nd digit*/

void digit2(int number) {
  if (number == 0) {
    board2.setPWM(1, 0, angleToPulse(88));delay(200); 
    board2.setPWM(0, 0, angleToPulse(46));delay(200); 
    board1.setPWM(15, 0, angleToPulse(120));delay(200); 
    board1.setPWM(14, 0, angleToPulse(45));delay(200); 
    board1.setPWM(13, 0, angleToPulse(119));delay(200); 
    board1.setPWM(12, 0, angleToPulse(78));delay(200);
    board2.setPWM(7, 0, angleToPulse(44));delay(200);
    board2.setPWM(6, 0, angleToPulse(6));delay(200);
    board2.setPWM(5, 0, angleToPulse(122));delay(200); 
    board2.setPWM(4, 0, angleToPulse(46));delay(200);
    board2.setPWM(3, 0, angleToPulse(124));delay(200);
    board2.setPWM(2, 0, angleToPulse(14));delay(200);
  }
  else if (number == 1) {
    board2.setPWM(1, 0, angleToPulse(33));delay(200);
    board2.setPWM(0, 0, angleToPulse(29));delay(200);
    board1.setPWM(15, 0, angleToPulse(25));delay(200);
    board1.setPWM(14, 0, angleToPulse(26));delay(200); 
    board1.setPWM(13, 0, angleToPulse(27));delay(200);
    board1.setPWM(12, 0, angleToPulse(21));delay(200); 
    board2.setPWM(7, 0, angleToPulse(44));delay(200);  
    board2.setPWM(6, 0, angleToPulse(37));delay(200); 
    board2.setPWM(5, 0, angleToPulse(122));delay(200); 
    board2.setPWM(4, 0, angleToPulse(46));delay(200); 
    board2.setPWM(3, 0, angleToPulse(125));delay(200); 
    board2.setPWM(2, 0, angleToPulse(120));delay(200);
  }
  else if (number == 2) {
    board2.setPWM(1, 0, angleToPulse(87));delay(200); 
    board2.setPWM(0, 0, angleToPulse(79));delay(200); 
    board1.setPWM(15, 0, angleToPulse(81));delay(200);
    board1.setPWM(14, 0, angleToPulse(44));delay(200); 
    board1.setPWM(13, 0, angleToPulse(119));delay(200); 
    board1.setPWM(12, 0, angleToPulse(83));delay(200); 
    board2.setPWM(7, 0, angleToPulse(44));delay(200);
    board2.setPWM(6, 0, angleToPulse(7));delay(200);
    board2.setPWM(5, 0, angleToPulse(122));delay(200);
    board2.setPWM(4, 0, angleToPulse(11));delay(200);
    board2.setPWM(3, 0, angleToPulse(18));delay(200); 
    board2.setPWM(2, 0, angleToPulse(14));delay(200);
  }
  else if (number == 3) {
    board2.setPWM(1, 0, angleToPulse(87));delay(200);
    board2.setPWM(0, 0, angleToPulse(79));delay(200);
    board1.setPWM(15, 0, angleToPulse(82));delay(200); 
    board1.setPWM(14, 0, angleToPulse(79));delay(200);
    board1.setPWM(13, 0, angleToPulse(79));delay(200); 
    board1.setPWM(12, 0, angleToPulse(84));delay(200); 
    board2.setPWM(7, 0, angleToPulse(44));delay(200); 
    board2.setPWM(6, 0, angleToPulse(7));delay(200);  
    board2.setPWM(5, 0, angleToPulse(122));delay(200); 
    board2.setPWM(4, 0, angleToPulse(11));delay(200); 
    board2.setPWM(3, 0, angleToPulse(124));delay(200);
    board2.setPWM(2, 0, angleToPulse(13));delay(200); 
  }
  else if (number == 4) {
    board2.setPWM(1, 0, angleToPulse(53));delay(200);
    board2.setPWM(0, 0, angleToPulse(47));delay(200);
    board1.setPWM(15, 0, angleToPulse(119));delay(200); 
    board1.setPWM(14, 0, angleToPulse(79));delay(200);
    board1.setPWM(13, 0, angleToPulse(27));delay(200);
    board1.setPWM(12, 0, angleToPulse(20));delay(200);
    board2.setPWM(7, 0, angleToPulse(44));delay(200); 
    board2.setPWM(6, 0, angleToPulse(37));delay(200); 
    board2.setPWM(5, 0, angleToPulse(122));delay(200);
    board2.setPWM(4, 0, angleToPulse(45));delay(200); 
    board2.setPWM(3, 0, angleToPulse(125));delay(200); 
    board2.setPWM(2, 0, angleToPulse(120));delay(200);
  }
  else if (number == 5) {
    board2.setPWM(1, 0, angleToPulse(88));delay(200); 
    board2.setPWM(0, 0, angleToPulse(45));delay(200); 
    board1.setPWM(15, 0, angleToPulse(119));delay(200); 
    board1.setPWM(14, 0, angleToPulse(80));delay(200); 
    board1.setPWM(13, 0, angleToPulse(78));delay(200);
    board1.setPWM(12, 0, angleToPulse(82));delay(200); 
    board2.setPWM(7, 0, angleToPulse(12));delay(200);
    board2.setPWM(6, 0, angleToPulse(7));delay(200);
    board2.setPWM(5, 0, angleToPulse(49));delay(200); 
    board2.setPWM(4, 0, angleToPulse(11));delay(200); 
    board2.setPWM(3, 0, angleToPulse(124));delay(200); 
    board2.setPWM(2, 0, angleToPulse(14));delay(200); 
  }
  else if (number == 6) {
    board2.setPWM(1, 0, angleToPulse(88));delay(200);
    board2.setPWM(0, 0, angleToPulse(45));delay(200);
    board1.setPWM(15, 0, angleToPulse(120));delay(200);
    board1.setPWM(14, 0, angleToPulse(44));delay(200); 
    board1.setPWM(13, 0, angleToPulse(120));delay(200); 
    board1.setPWM(12, 0, angleToPulse(78));delay(200);
    board2.setPWM(7, 0, angleToPulse(12));delay(200);
    board2.setPWM(6, 0, angleToPulse(7));delay(200);
    board2.setPWM(5, 0, angleToPulse(49));delay(200); 
    board2.setPWM(4, 0, angleToPulse(11));delay(200);
    board2.setPWM(3, 0, angleToPulse(124));delay(200);
    board2.setPWM(2, 0, angleToPulse(14));delay(200); 
  }
  else if (number == 7) {
    board2.setPWM(1, 0, angleToPulse(87));delay(200);
    board2.setPWM(0, 0, angleToPulse(79));delay(200);
    board1.setPWM(15, 0, angleToPulse(25));delay(200);
    board1.setPWM(14, 0, angleToPulse(26));delay(200);
    board1.setPWM(13, 0, angleToPulse(27));delay(200);
    board1.setPWM(12, 0, angleToPulse(21));delay(200);
    board2.setPWM(7, 0, angleToPulse(43));delay(200);
    board2.setPWM(6, 0, angleToPulse(6));delay(200); 
    board2.setPWM(5, 0, angleToPulse(122));delay(200);
    board2.setPWM(4, 0, angleToPulse(45));delay(200); 
    board2.setPWM(3, 0, angleToPulse(125));delay(200);
    board2.setPWM(2, 0, angleToPulse(120));delay(200);
  }
  else if (number == 8) {
    board2.setPWM(1, 0, angleToPulse(88));delay(200);
    board2.setPWM(0, 0, angleToPulse(46));delay(200);
    board1.setPWM(15, 0, angleToPulse(120));delay(200);
    board1.setPWM(14, 0, angleToPulse(80));delay(200); 
    board1.setPWM(13, 0, angleToPulse(119));delay(200); 
    board1.setPWM(12, 0, angleToPulse(83));delay(200);
    board2.setPWM(7, 0, angleToPulse(44));delay(200); 
    board2.setPWM(6, 0, angleToPulse(6));delay(200); 
    board2.setPWM(5, 0, angleToPulse(122));delay(200); 
    board2.setPWM(4, 0, angleToPulse(11));delay(200);
    board2.setPWM(3, 0, angleToPulse(124));delay(200);
    board2.setPWM(2, 0, angleToPulse(14));delay(200);
  }
  else if (number == 9) {
    board2.setPWM(1, 0, angleToPulse(88));delay(200); 
    board2.setPWM(0, 0, angleToPulse(46));delay(200);
    board1.setPWM(15, 0, angleToPulse(120));delay(200);
    board1.setPWM(14, 0, angleToPulse(80));delay(200);
    board1.setPWM(13, 0, angleToPulse(79));delay(200); 
    board1.setPWM(12, 0, angleToPulse(84));delay(200);
    board2.setPWM(7, 0, angleToPulse(44));delay(200);
    board2.setPWM(6, 0, angleToPulse(6));delay(200);
    board2.setPWM(5, 0, angleToPulse(122));delay(200); 
    board2.setPWM(4, 0, angleToPulse(45));delay(200); 
    board2.setPWM(3, 0, angleToPulse(124));delay(200);
    board2.setPWM(2, 0, angleToPulse(14));delay(200);
  }
}

/*3rd digit*/

void digit3(int number) {
  if (number == 0) {
    board2.setPWM(13, 0, angleToPulse(86.5));delay(200);
    board2.setPWM(12, 0, angleToPulse(53));delay(200);
    board2.setPWM(11, 0, angleToPulse(120));delay(200);
    board2.setPWM(10, 0, angleToPulse(52));delay(200);
    board2.setPWM(9, 0, angleToPulse(124));delay(200);
    board2.setPWM(8, 0, angleToPulse(85));delay(200);
    board2.setPWM(15, 0, angleToPulse(43));delay(200);
    board2.setPWM(14, 0, angleToPulse(18));delay(200); 
    board3.setPWM(1, 0, angleToPulse(122));delay(200);
    board3.setPWM(0, 0, angleToPulse(46));delay(200);
    board3.setPWM(3, 0, angleToPulse(125.5));delay(200); 
    board3.setPWM(2, 0, angleToPulse(24));delay(200);
  }
  else if (number == 1) {
    board2.setPWM(13, 0, angleToPulse(32));delay(200);
    board2.setPWM(12, 0, angleToPulse(33));delay(200);
    board2.setPWM(11, 0, angleToPulse(32));delay(200);
    board2.setPWM(10, 0, angleToPulse(35));delay(200);
    board2.setPWM(9, 0, angleToPulse(38));delay(200);
    board2.setPWM(8, 0, angleToPulse(30));delay(200);
    board2.setPWM(15, 0, angleToPulse(42));delay(200);
    board2.setPWM(14, 0, angleToPulse(52));delay(200);
    board3.setPWM(1, 0, angleToPulse(122));delay(200);
    board3.setPWM(0, 0, angleToPulse(46));delay(200);
    board3.setPWM(3, 0, angleToPulse(125));delay(200);
    board3.setPWM(2, 0, angleToPulse(124));delay(200);
  }
  else if (number == 2) {
    board2.setPWM(13, 0, angleToPulse(86));delay(200); 
    board2.setPWM(12, 0, angleToPulse(90.5));delay(200);  
    board2.setPWM(11, 0, angleToPulse(83));delay(200);
    board2.setPWM(10, 0, angleToPulse(50));delay(200); 
    board2.setPWM(9, 0, angleToPulse(124.5));delay(200); 
    board2.setPWM(8, 0, angleToPulse(83.5));delay(200); 
    board2.setPWM(15, 0, angleToPulse(43));delay(200); 
    board2.setPWM(14, 0, angleToPulse(18));delay(200);
    board3.setPWM(1, 0, angleToPulse(122));delay(200);
    board3.setPWM(0, 0, angleToPulse(12));delay(200);
    board3.setPWM(3, 0, angleToPulse(27));delay(200);
    board3.setPWM(2, 0, angleToPulse(24));delay(200);
  }
  else if (number == 3) {
    board2.setPWM(13, 0, angleToPulse(86));delay(200);
    board2.setPWM(12, 0, angleToPulse(90));delay(200);
    board2.setPWM(11, 0, angleToPulse(83));delay(200); 
    board2.setPWM(10, 0, angleToPulse(87));delay(200);
    board2.setPWM(9, 0, angleToPulse(91));delay(200);
    board2.setPWM(8, 0, angleToPulse(84));delay(200); 
    board2.setPWM(15, 0, angleToPulse(43));delay(200);
    board2.setPWM(14, 0, angleToPulse(18));delay(200);
    board3.setPWM(1, 0, angleToPulse(122));delay(200);
    board3.setPWM(0, 0, angleToPulse(12));delay(200);
    board3.setPWM(3, 0, angleToPulse(125));delay(200);
    board3.setPWM(2, 0, angleToPulse(22));delay(200);
  }
  else if (number == 4) {
    board2.setPWM(13, 0, angleToPulse(49));delay(200);
    board2.setPWM(12, 0, angleToPulse(54));delay(200);
    board2.setPWM(11, 0, angleToPulse(120));delay(200);
    board2.setPWM(10, 0, angleToPulse(86));delay(200);
    board2.setPWM(9, 0, angleToPulse(38));delay(200);
    board2.setPWM(8, 0, angleToPulse(30));delay(200);
    board2.setPWM(15, 0, angleToPulse(42));delay(200); 
    board2.setPWM(14, 0, angleToPulse(52));delay(200);
    board3.setPWM(1, 0, angleToPulse(122));delay(200);
    board3.setPWM(0, 0, angleToPulse(47));delay(200); 
    board3.setPWM(3, 0, angleToPulse(126));delay(200);
    board3.setPWM(2, 0, angleToPulse(124));delay(200);  
  }
  else if (number == 5) {
    board2.setPWM(13, 0, angleToPulse(86.5));delay(200); 
    board2.setPWM(12, 0, angleToPulse(53));delay(200);
    board2.setPWM(11, 0, angleToPulse(120));delay(200);
    board2.setPWM(10, 0, angleToPulse(86));delay(200); 
    board2.setPWM(9, 0, angleToPulse(90));delay(200);
    board2.setPWM(8, 0, angleToPulse(85));delay(200);
    board2.setPWM(15, 0, angleToPulse(8));delay(200);
    board2.setPWM(14, 0, angleToPulse(21));delay(200);
    board3.setPWM(1, 0, angleToPulse(49));delay(200); 
    board3.setPWM(0, 0, angleToPulse(16));delay(200); 
    board3.setPWM(3, 0, angleToPulse(125));delay(200);
    board3.setPWM(2, 0, angleToPulse(24));delay(200);
  }
}

/*4th digit*/

void digit4(int number) {
  if (number == 0) {
    board3.setPWM(9, 0, angleToPulse(80));delay(200);
    board3.setPWM(8, 0, angleToPulse(54));delay(200); 
    board3.setPWM(7, 0, angleToPulse(116));delay(200);
    board3.setPWM(6, 0, angleToPulse(54));delay(200); 
    board3.setPWM(5, 0, angleToPulse(115));delay(200);
    board3.setPWM(4, 0, angleToPulse(89));delay(200); 
    board3.setPWM(15, 0, angleToPulse(20));delay(200);
    board3.setPWM(14, 0, angleToPulse(53));delay(200); 
    board3.setPWM(13, 0, angleToPulse(121));delay(200); 
    board3.setPWM(12, 0, angleToPulse(56));delay(200);
    board3.setPWM(11, 0, angleToPulse(117));delay(200); 
    board3.setPWM(10, 0, angleToPulse(21));delay(200); 
  }
  else if (number == 1) {
    board3.setPWM(9, 0, angleToPulse(28));delay(200);
    board3.setPWM(8, 0, angleToPulse(36));delay(200);
    board3.setPWM(7, 0, angleToPulse(36.5));delay(200); 
    board3.setPWM(6, 0, angleToPulse(33.5));delay(200); 
    board3.setPWM(5, 0, angleToPulse(32));delay(200);   
    board3.setPWM(4, 0, angleToPulse(33));delay(200);
    board3.setPWM(15, 0, angleToPulse(54));delay(200); 
    board3.setPWM(14, 0, angleToPulse(52));delay(200); 
    board3.setPWM(13, 0, angleToPulse(121));delay(200); 
    board3.setPWM(12, 0, angleToPulse(56));delay(200); 
    board3.setPWM(11, 0, angleToPulse(119));delay(200); 
    board3.setPWM(10, 0, angleToPulse(120));delay(200); 
  }
  else if (number == 2) {
    board3.setPWM(9, 0, angleToPulse(78));delay(200); 
    board3.setPWM(8, 0, angleToPulse(88));delay(200);
    board3.setPWM(7, 0, angleToPulse(82));delay(200); 
    board3.setPWM(6, 0, angleToPulse(50));delay(200);
    board3.setPWM(5, 0, angleToPulse(116));delay(200); 
    board3.setPWM(4, 0, angleToPulse(88));delay(200); 
    board3.setPWM(15, 0, angleToPulse(22));delay(200); 
    board3.setPWM(14, 0, angleToPulse(54));delay(200);
    board3.setPWM(13, 0, angleToPulse(122));delay(200); 
    board3.setPWM(12, 0, angleToPulse(23));delay(200); 
    board3.setPWM(11, 0, angleToPulse(20));delay(200); 
    board3.setPWM(10, 0, angleToPulse(22));delay(200); 
  }
  else if (number == 3) {
    board3.setPWM(9, 0, angleToPulse(78));delay(200);
    board3.setPWM(8, 0, angleToPulse(88));delay(200); 
    board3.setPWM(7, 0, angleToPulse(82));delay(200);
    board3.setPWM(6, 0, angleToPulse(86));delay(200); 
    board3.setPWM(5, 0, angleToPulse(85));delay(200);
    board3.setPWM(4, 0, angleToPulse(88));delay(200);
    board3.setPWM(15, 0, angleToPulse(22));delay(200); 
    board3.setPWM(14, 0, angleToPulse(54));delay(200);
    board3.setPWM(13, 0, angleToPulse(122));delay(200); 
    board3.setPWM(12, 0, angleToPulse(23));delay(200); 
    board3.setPWM(11, 0, angleToPulse(118));delay(200);
    board3.setPWM(10, 0, angleToPulse(21));delay(200);
  }
  else if (number == 4) {
    board3.setPWM(9, 0, angleToPulse(43));delay(200); 
    board3.setPWM(8, 0, angleToPulse(56));delay(200);
    board3.setPWM(7, 0, angleToPulse(116));delay(200); 
    board3.setPWM(6, 0, angleToPulse(87));delay(200); 
    board3.setPWM(5, 0, angleToPulse(32));delay(200);
    board3.setPWM(4, 0, angleToPulse(33));delay(200);
    board3.setPWM(15, 0, angleToPulse(54));delay(200); 
    board3.setPWM(14, 0, angleToPulse(52));delay(200);
    board3.setPWM(13, 0, angleToPulse(121));delay(200); 
    board3.setPWM(12, 0, angleToPulse(56));delay(200); 
    board3.setPWM(11, 0, angleToPulse(118));delay(200); 
    board3.setPWM(10, 0, angleToPulse(119));delay(200); 
  }
  else if (number == 5) {
    board3.setPWM(9, 0, angleToPulse(80));delay(200);
    board3.setPWM(8, 0, angleToPulse(54));delay(200);
    board3.setPWM(7, 0, angleToPulse(116));delay(200); 
    board3.setPWM(6, 0, angleToPulse(87));delay(200); 
    board3.setPWM(5, 0, angleToPulse(85));delay(200);
    board3.setPWM(4, 0, angleToPulse(88));delay(200); 
    board3.setPWM(15, 0, angleToPulse(21));delay(200);
    board3.setPWM(14, 0, angleToPulse(21));delay(200); 
    board3.setPWM(13, 0, angleToPulse(52));delay(200);
    board3.setPWM(12, 0, angleToPulse(22));delay(200);
    board3.setPWM(11, 0, angleToPulse(118));delay(200); 
    board3.setPWM(10, 0, angleToPulse(22));delay(200);
  }
  else if (number == 6) {
    board3.setPWM(9, 0, angleToPulse(80));delay(200);
    board3.setPWM(8, 0, angleToPulse(54));delay(200);
    board3.setPWM(7, 0, angleToPulse(116));delay(200);
    board3.setPWM(6, 0, angleToPulse(54));delay(200); 
    board3.setPWM(5, 0, angleToPulse(115));delay(200); 
    board3.setPWM(4, 0, angleToPulse(89));delay(200); 
    board3.setPWM(15, 0, angleToPulse(21));delay(200);
    board3.setPWM(14, 0, angleToPulse(21));delay(200);
    board3.setPWM(13, 0, angleToPulse(52));delay(200);
    board3.setPWM(12, 0, angleToPulse(22));delay(200);
    board3.setPWM(11, 0, angleToPulse(118));delay(200);
    board3.setPWM(10, 0, angleToPulse(22));delay(200);
  }
  else if (number == 7) {
    board3.setPWM(9, 0, angleToPulse(80));delay(200); 
    board3.setPWM(8, 0, angleToPulse(87.5));delay(200);
    board3.setPWM(7, 0, angleToPulse(36.5));delay(200); 
    board3.setPWM(6, 0, angleToPulse(33.5));delay(200); 
    board3.setPWM(5, 0, angleToPulse(32));delay(200); 
    board3.setPWM(4, 0, angleToPulse(33));delay(200);
    board3.setPWM(15, 0, angleToPulse(20));delay(200); 
    board3.setPWM(14, 0, angleToPulse(53));delay(200); 
    board3.setPWM(13, 0, angleToPulse(121));delay(200); 
    board3.setPWM(12, 0, angleToPulse(57));delay(200); 
    board3.setPWM(11, 0, angleToPulse(118));delay(200);
    board3.setPWM(10, 0, angleToPulse(119));delay(200);
  }
  else if (number == 8) {
    board3.setPWM(9, 0, angleToPulse(80));delay(200);
    board3.setPWM(8, 0, angleToPulse(54));delay(200); 
    board3.setPWM(7, 0, angleToPulse(116));delay(200); 
    board3.setPWM(6, 0, angleToPulse(87));delay(200); 
    board3.setPWM(5, 0, angleToPulse(117));delay(200);
    board3.setPWM(4, 0, angleToPulse(88));delay(200); 
    board3.setPWM(15, 0, angleToPulse(20));delay(200);
    board3.setPWM(14, 0, angleToPulse(53));delay(200);
    board3.setPWM(13, 0, angleToPulse(122));delay(200); 
    board3.setPWM(12, 0, angleToPulse(23));delay(200); 
    board3.setPWM(11, 0, angleToPulse(117));delay(200);
    board3.setPWM(10, 0, angleToPulse(21));delay(200); 
  }
  else if (number == 9) {
    board3.setPWM(9, 0, angleToPulse(80));delay(200);
    board3.setPWM(8, 0, angleToPulse(54));delay(200); 
    board3.setPWM(7, 0, angleToPulse(116));delay(200); 
    board3.setPWM(6, 0, angleToPulse(87));delay(200); 
    board3.setPWM(5, 0, angleToPulse(85));delay(200); 
    board3.setPWM(4, 0, angleToPulse(88));delay(200);  
    board3.setPWM(15, 0, angleToPulse(20));delay(200); 
    board3.setPWM(14, 0, angleToPulse(53));delay(200); 
    board3.setPWM(13, 0, angleToPulse(121));delay(200);
    board3.setPWM(12, 0, angleToPulse(56));delay(200); 
    board3.setPWM(11, 0, angleToPulse(117));delay(200); 
    board3.setPWM(10, 0, angleToPulse(21));delay(200); 
  }
}
