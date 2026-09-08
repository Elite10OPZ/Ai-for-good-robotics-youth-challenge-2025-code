#include <Wire.h>
#include <MPU6050.h>
MPU6050 mpu;

// Motor control pins
const int in1 = 8, in2 = 9, in3 = 10, in4 = 11;
const int enA = 5; // Left motor speed
const int enB = 6; // Right motor speed

// Gyro variables
float angleZ = 0;
float gyroZ_bias = 0;
unsigned long lastTime;

void setup() {
  Serial.begin(9600);

  // Motor setup
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  analogWrite(enA, 150);
  analogWrite(enB, 150);

  // MPU setup
  Wire.begin();
  mpu.initialize();
  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed!");
    while (1);
  }

  delay(800);
  gyroZ_bias = calibrateGyroZ();
  Serial.print("Gyro Z Bias: ");
  Serial.println(gyroZ_bias);
  lastTime = millis();
}

void loop() {
  moveForwardWithCorrection(200);
  stopp();
  delay(500);

  turnToAngle(-40); // Left
  stopp();
  delay(500);

  moveForwardWithCorrection(1500);
  stopp();
  delay(500);

  turnToAngle(45); // Right
  stopp();
  delay(500);

  moveForwardWithCorrection(1350);
  stopp();
  delay(500);

  turnToAngle(75);
  stopp();
  delay(500);

  moveForwardWithCorrection(1900);
  stopp();
  delay(500);

  turnToAngle(150);
  stopp();
  delay(300);

  moveForwardWithCorrection(4500);
  stopp();
  delay(1000);

  //a..a

  backward();
  delay(600);

moveForwardWithCorrection(1000);
stopp();
delay(400);
backward();
delay(800);


  turnToAngle(95);
  stopp();
  delay(400);

  moveForwardWithCorrection(2670);
  stopp();

  turnToAngle(75);
  stopp();

  moveForwardWithCorrection(3300);
  stopp();

  turnToAngle(75);
  stopp();
  
  moveForwardWithCorrection(3200);
  stopp();
  delay(2000);
  backward();
  delay(4000);
  stopp();
  turnToAngle(90);
  stopp();
  delay(300);
  moveForwardWithCorrection(2000);
  stopp();
  turnToAngle(-135);
  stopp();
  delay(300);
  moveForwardWithCorrection(6000);
  stopp();

  delay(100000); 
}

// === Movement with correction ===
void moveForwardWithCorrection(int duration_ms) {
  unsigned long start = millis();
  angleZ = 0;
  lastTime = millis();

  while (millis() - start < duration_ms) {
    float gyroZ = readGyroZ();
    float elapsedTime = (millis() - lastTime) / 1000.0;
    lastTime = millis();
    angleZ += gyroZ * elapsedTime;

    if (angleZ > -3 && angleZ < 3) {
      forward();
    } else if (angleZ < -3) {
      slightRight();
    } else if (angleZ > 3) {
      slightLeft();
    }
    delay(10);
  }
  stopp();
}

// === Turn to angle using gyro ===
void turnToAngle(float targetAngle) {
  angleZ = 0;
  lastTime = millis();

  if (targetAngle < 0) {
    // Turn Left
    while (angleZ > targetAngle) {
      float gyroZ = readGyroZ();
      float elapsed = (millis() - lastTime) / 1000.0;
      lastTime = millis();
      angleZ += gyroZ * elapsed;
      Serial.print("Turning Left AngleZ: "); Serial.println(angleZ);
      leftone();  // corrected left turn
      delay(10);
    }
  } else {
    // Turn Right
    while (angleZ < targetAngle) {
      float gyroZ = readGyroZ();
      float elapsed = (millis() - lastTime) / 1000.0;
      lastTime = millis();
      angleZ += gyroZ * elapsed;
      Serial.print("Turning Right AngleZ: "); Serial.println(angleZ);
      rightone(); // corrected right turn
      delay(10);
    }
  }
  stopp();
}

// === Motor Functions ===
void forward() {
  analogWrite(enA, 150); analogWrite(enB, 150);
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
}

void backward() {
  analogWrite(enA, 150); analogWrite(enB, 150);
  digitalWrite(in1, LOW); digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW); digitalWrite(in4, HIGH);
}

void slightLeft() {
  analogWrite(enA, 100); analogWrite(enB, 150);
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
}

void slightRight() {
  analogWrite(enA, 150); analogWrite(enB, 100);
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
}

void leftone() {
  analogWrite(enA, 150); analogWrite(enB, 0);
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);  digitalWrite(in4, LOW);
}
// === Gyro calibration ===

void rightone() {
  analogWrite(enA, 0); analogWrite(enB, 150);
  digitalWrite(in1, LOW);  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
}

void stopp() {
  digitalWrite(in1, LOW); digitalWrite(in2, LOW);
  digitalWrite(in3, LOW); digitalWrite(in4, LOW);
}

float calibrateGyroZ() {
  long sum = 0;
  int samples = 500;
  int16_t gx, gy, gz;

  for (int i = 0; i < samples; i++) {
    mpu.getRotation(&gx, &gy, &gz);
    sum += gz;
    delay(5);
  }
  return (float)sum / samples / 131.0;
}

// === Gyro reading ===
float readGyroZ() {
  int16_t gx, gy, gz;
  mpu.getRotation(&gx, &gy, &gz);
  float gyroZ = (float)gz / 131.0;
  gyroZ -= gyroZ_bias;
  return gyroZ;
}