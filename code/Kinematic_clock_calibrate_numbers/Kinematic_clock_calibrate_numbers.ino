#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver board1 = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver board2 = Adafruit_PWMServoDriver(0x41);
Adafruit_PWMServoDriver board3 = Adafruit_PWMServoDriver(0x42);

#define SERVOMIN  544 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  2400// This is the 'maximum' pulse length count (out of 4096)
//#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
//#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

int number; // Number command 

void setup() {  

Serial.begin(9600); 

board1.begin();  // Initialize servo ccontrol boards 
board2.begin();
board3.begin();
board1.setOscillatorFrequency(27000000);
board2.setOscillatorFrequency(27000000);
board3.setOscillatorFrequency(27000000);
board1.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
board2.setPWMFreq(SERVO_FREQ); 
board3.setPWMFreq(SERVO_FREQ); 

Serial.println("Ready for command");

yield();
}

void loop() {  

while(Serial.available()>0){  // See if a command has been sent
  number = Serial.parseInt(); // Turn command into integer
  Serial.print(number);
  Serial.println(" sent");
  digit4(number); // Change between digit1 - digit4, depending on which digit is being calibrated
}
delay(1000);
}

int angleToPulse(int ang){
   int pulse1 = map(ang,0, 180, SERVOMIN,SERVOMAX); // Map angle of 0 to 180 to Servo min and Servo max 
   int pulse2 = int(float(pulse1) / 1000000 * SERVO_FREQ * 4096);
   Serial.print("Angle: ");Serial.print(ang);
   Serial.print(" pulse: ");Serial.println(pulse2);
   return pulse2;
}

/*1st digit*/

void digit1(int number) {
  if (number == 11) {
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
  if (number == 11) {
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
  if (number ==11) {
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
 
