#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

// =====================================================
// TB6612FNG #1  (MOTOR 1 + MOTOR 2)
// =====================================================

// Motor 1
const int AIN1_1 = 5;
const int AIN2_1 = 4;
const int PWMA_1 = 7;

// Motor 2
const int BIN1_1 = 3;
const int BIN2_1 = 2;
const int PWMB_1 = 6;


// =====================================================
// TB6612FNG #2  (MOTOR 3 + MOTOR 4)
// =====================================================

// Motor 3
const int AIN1_2 = 11;
const int AIN2_2 = 10;
const int PWMA_2 = 13;

// Motor 4
const int BIN1_2 = 9;
const int BIN2_2 = 8;
const int PWMB_2 = 12;

// =====================================================

void setup() {

  Serial.begin(115200);
  Serial.println("Starting 4 Motor + MPU6050 Test");

  // =====================================================
  // MPU6050
  // =====================================================

  Wire.begin();

  mpu.initialize();

  if (mpu.testConnection()) {
    Serial.println("MPU6050 connected successfully!");
  } else {
    Serial.println("MPU6050 connection failed!");
  }

  // =====================================================
  // MOTOR DRIVER 1
  // =====================================================

  pinMode(AIN1_1, OUTPUT);
  pinMode(AIN2_1, OUTPUT);
  pinMode(PWMA_1, OUTPUT);

  pinMode(BIN1_1, OUTPUT);
  pinMode(BIN2_1, OUTPUT);
  pinMode(PWMB_1, OUTPUT);

  // =====================================================
  // MOTOR DRIVER 2
  // =====================================================

  pinMode(AIN1_2, OUTPUT);
  pinMode(AIN2_2, OUTPUT);
  pinMode(PWMA_2, OUTPUT);

  pinMode(BIN1_2, OUTPUT);
  pinMode(BIN2_2, OUTPUT);
  pinMode(PWMB_2, OUTPUT);

  stopAllMotors();

  delay(1000);
}

void loop() {

  // =====================================================
  // TEST 1: ALL MOTORS FORWARD
  // =====================================================

  Serial.println("ALL MOTORS FORWARD");

  motor1Forward(180);
  motor2Forward(180);
  motor3Forward(180);
  motor4Forward(180);

  printIMU();

  delay(3000);

  // =====================================================
  // STOP
  // =====================================================

  Serial.println("STOP");

  stopAllMotors();

  delay(1000);

  // =====================================================
  // TEST 2: ALL MOTORS BACKWARD
  // =====================================================

  Serial.println("ALL MOTORS BACKWARD");

  motor1Backward(180);
  motor2Backward(180);
  motor3Backward(180);
  motor4Backward(180);

  printIMU();

  delay(3000);

  // =====================================================
  // STOP
  // =====================================================

  Serial.println("STOP");

  stopAllMotors();

  printIMU();

  delay(2000);
}

// =====================================================
// MOTOR 1
// =====================================================

void motor1Forward(int speedVal) {

  digitalWrite(AIN1_1, HIGH);
  digitalWrite(AIN2_1, LOW);

  analogWrite(PWMA_1, speedVal);
}

void motor1Backward(int speedVal) {

  digitalWrite(AIN1_1, LOW);
  digitalWrite(AIN2_1, HIGH);

  analogWrite(PWMA_1, speedVal);
}

// =====================================================
// MOTOR 2
// =====================================================

void motor2Forward(int speedVal) {

  digitalWrite(BIN1_1, HIGH);
  digitalWrite(BIN2_1, LOW);

  analogWrite(PWMB_1, speedVal);
}

void motor2Backward(int speedVal) {

  digitalWrite(BIN1_1, LOW);
  digitalWrite(BIN2_1, HIGH);

  analogWrite(PWMB_1, speedVal);
}

// =====================================================
// MOTOR 3
// =====================================================

void motor3Forward(int speedVal) {

  digitalWrite(AIN1_2, HIGH);
  digitalWrite(AIN2_2, LOW);

  analogWrite(PWMA_2, speedVal);
}

void motor3Backward(int speedVal) {

  digitalWrite(AIN1_2, LOW);
  digitalWrite(AIN2_2, HIGH);

  analogWrite(PWMA_2, speedVal);
}

// =====================================================
// MOTOR 4
// =====================================================

void motor4Forward(int speedVal) {

  digitalWrite(BIN1_2, HIGH);
  digitalWrite(BIN2_2, LOW);

  analogWrite(PWMB_2, speedVal);
}

void motor4Backward(int speedVal) {

  digitalWrite(BIN1_2, LOW);
  digitalWrite(BIN2_2, HIGH);

  analogWrite(PWMB_2, speedVal);
}

// =====================================================
// STOP ALL MOTORS
// =====================================================

void stopAllMotors() {

  analogWrite(PWMA_1, 0);
  analogWrite(PWMB_1, 0);

  analogWrite(PWMA_2, 0);
  analogWrite(PWMB_2, 0);

  digitalWrite(AIN1_1, LOW);
  digitalWrite(AIN2_1, LOW);

  digitalWrite(BIN1_1, LOW);
  digitalWrite(BIN2_1, LOW);

  digitalWrite(AIN1_2, LOW);
  digitalWrite(AIN2_2, LOW);

  digitalWrite(BIN1_2, LOW);
  digitalWrite(BIN2_2, LOW);
}

// =====================================================
// MPU6050 PRINT FUNCTION
// =====================================================

void printIMU() {

  int16_t ax, ay, az;
  int16_t gx, gy, gz;

  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  Serial.print("ACC -> ");

  Serial.print("X: ");
  Serial.print(ax);

  Serial.print("  Y: ");
  Serial.print(ay);

  Serial.print("  Z: ");
  Serial.print(az);

  Serial.print("   GYRO -> ");

  Serial.print("X: ");
  Serial.print(gx);

  Serial.print("  Y: ");
  Serial.print(gy);

  Serial.print("  Z: ");
  Serial.println(gz);
}