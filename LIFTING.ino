#define dirPin 2
#define stepPin 3
#define stepsPerRevolution 2000
#define stepsPerRevolution1 1000
#include <Servo.h>  // Include the Servo library which allows us to control servo motors
Servo myservo;  // Create a Servo object named myservo to control a servo motor
#include <Wire.h>
unsigned long lastTime = 0;
void setup() {
  pinMode(8,OUTPUT);   //left motors reverse
pinMode(9,OUTPUT);   //left motors reverse
pinMode(10,OUTPUT);   //right motors forward
pinMode(11,OUTPUT);   //right motors reverse
pinMode(5,OUTPUT);  
pinMode(6,OUTPUT);  
analogWrite(5,180);
analogWrite(6,180);
Serial.begin(9600);
 myservo.attach(7);
  myservo.write(90);//close 
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  analogWrite(5, 180);
  analogWrite(6, 180);

  // MPU setup

}


void loop() {
  

 

//delay(60000);
forward();
delay(2000);
  stopp();
  delay(1000);
right();
delay(1000);
  stopp();
  delay(1000);
  myservo.write(60);//open
  delay(1000);
  down();
  delay(1000);
forward();
delay(2000);
  stopp();
  delay(1000);
  myservo.write(90);
  delay(1000);
  up();
  delay(1000);
  right();
  delay(500);
    stopp();
  delay(1000);
  forward();
  delay(1000);
    stopp();
  delay(1000);
  down1();
  delay(1000);
   myservo.write(60);
  delay(1000);
  backward();
    delay(2000);
        stopp();
  delay(1000);
  up1();
  delay(1000);

  stopp();
  delay(1000000);
  */
}
void up()
{
    digitalWrite(dirPin, HIGH);

  // Spin the stepper motor 1 revolution slowly:
  for (int i = 0; i < 10*stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(200);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(200);
  }

  delay(1000);
}
void up1()
{
    digitalWrite(dirPin, HIGH);

  // Spin the stepper motor 1 revolution slowly:
  for (int i = 0; i < 10*stepsPerRevolution1; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(200);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(200);
  }

  delay(1000);
}
void down()
{
    digitalWrite(dirPin, LOW);

  // Spin the stepper motor 1 revolution quickly:
  for (int i = 0; i < 10*stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(200);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(200);
  }

  delay(1000);
}
void down1()
{
    digitalWrite(dirPin, LOW);

  // Spin the stepper motor 1 revolution quickly:
  for (int i = 0; i < 10*stepsPerRevolution1; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(200);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(200);
  }

  delay(1000);
}
void backward()
{            //move forward(all motors rotate in forward direction)
  digitalWrite(8,HIGH);
  digitalWrite(9,LOW);
  digitalWrite(10,HIGH);
  digitalWrite(11,LOW);
}
 
void forward(){      //move reverse (all motors rotate in reverse direction)
  digitalWrite(8,LOW);
  digitalWrite(9,HIGH);
  digitalWrite(10,LOW);
  digitalWrite(11,HIGH);
}

void right() 
{      //turn right (left side motors rotate in forward direction, right side motors doesn't rotate)
  digitalWrite(8,LOW);
  digitalWrite(9,HIGH);
  digitalWrite(10,HIGH);
  digitalWrite(11,LOW);
}
void left()
{      //turn left (right side motors rotate in forward direction, left side motors doesn't rotate)
  digitalWrite(8,HIGH);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,HIGH);
 
}
 
void stopp() 
{      //STOP (all motors stop)
  digitalWrite(8,LOW);
  digitalWrite(9,LOW); 
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);

}
void sharpLeft() {
  analogWrite(5, 0);
  analogWrite(6, 180);
  digitalWrite(8, LOW);  digitalWrite(9, LOW);    // Left motor stopped
  digitalWrite(10, LOW);  digitalWrite(11, HIGH);   // Right motor forward
}
void sharpRight() {
  analogWrite(5, 180);
  analogWrite(6, 0);
  digitalWrite(8, LOW);  digitalWrite(9, HIGH);   // Left motor forward
  digitalWrite(10, LOW);  digitalWrite(11, LOW);    // Right motor stopped
}
void slightLeft() {
  digitalWrite(8, LOW);  digitalWrite(9, HIGH);   // Left motor forward
  digitalWrite(10, LOW); digitalWrite(11, HIGH);  // Right motor forward (same speed)
  delay(100);                                      // Slight delay
  digitalWrite(10, LOW); digitalWrite(11, LOW);   // Briefly stop right motor
  // This causes a small drift to the left
}

void slightRight() {
  digitalWrite(8, LOW);  digitalWrite(9, HIGH);   // Left motor forward (same speed)
  digitalWrite(10, LOW); digitalWrite(11, HIGH);  // Right motor forward
  delay(100);                                      // Slight delay
  digitalWrite(8, LOW);  digitalWrite(9, LOW);    // Briefly stop left motor
  // This causes a small drift to the right
}

