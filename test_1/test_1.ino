#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

// =====================================================
// MOTOR PINS
// =====================================================

// Motor 1
const int AIN1_1 = 5;
const int AIN2_1 = 4;
const int PWMA_1 = 7;

// Motor 2
const int BIN1_1 = 3;
const int BIN2_1 = 2;
const int PWMB_1 = 6;

// Motor 3
const int AIN1_2 = 11;
const int AIN2_2 = 10;
const int PWMA_2 = 13;

// Motor 4
const int BIN1_2 = 9;
const int BIN2_2 = 8;
const int PWMB_2 = 12;

// =====================================================
// CONTROL PARAMETERS
// =====================================================

float Kp = 15.0;
float Kd = 2.0;

float targetRoll = 0.0;

unsigned long lastTime = 0;

// =====================================================

void setup() {

  Serial.begin(115200);

  Wire.begin();

  mpu.initialize();

  if (mpu.testConnection()) {
    Serial.println("MPU6050 connected");
  } else {
    Serial.println("MPU6050 failed");
  }

  // Motor pins
  pinMode(AIN1_1, OUTPUT);
  pinMode(AIN2_1, OUTPUT);
  pinMode(PWMA_1, OUTPUT);

  pinMode(BIN1_1, OUTPUT);
  pinMode(BIN2_1, OUTPUT);
  pinMode(PWMB_1, OUTPUT);

  pinMode(AIN1_2, OUTPUT);
  pinMode(AIN2_2, OUTPUT);
  pinMode(PWMA_2, OUTPUT);

  pinMode(BIN1_2, OUTPUT);
  pinMode(BIN2_2, OUTPUT);
  pinMode(PWMB_2, OUTPUT);

  stopAllMotors();

  delay(1000);

  lastTime = millis();
}

// =====================================================

void loop() {

  unsigned long currentTime = millis();

  float dt =
      (currentTime - lastTime) / 1000.0;

  if (dt <= 0)
    return;

  lastTime = currentTime;

  // =====================================================
  // READ MPU
  // =====================================================

  int16_t ax, ay, az;
  int16_t gx, gy, gz;

  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Roll angle
  float roll =
      atan2((float)ay, (float)az)
      * 180.0 / PI;

  // Roll angular velocity
  float gyroRate =
      (float)gx / 131.0;

  // =====================================================
  // PD CONTROLLER
  // =====================================================

  float error =
      targetRoll - roll;

  float control =
      Kp * error
      - Kd * gyroRate;

  // =====================================================
  // DEADZONE
  // =====================================================

  if (abs(roll) < 1.0) {

    stopAllMotors();

  } else {

    int pwm =
        constrain(abs(control), 0, 120);

    // =================================================
    // PUSH RIGHT
    // =================================================

    if (control > 0) {

      allForward(pwm);

    }

    // =================================================
    // PUSH LEFT
    // =================================================

    else {

      allBackward(pwm);
    }
  }

  // =====================================================
  // DEBUG
  // =====================================================

  Serial.print("Roll: ");
  Serial.print(roll);

  Serial.print("  Gyro: ");
  Serial.print(gyroRate);

  Serial.print("  Control: ");
  Serial.println(control);
}

// =====================================================
// ALL FORWARD
// =====================================================

void allForward(int speedVal) {

  motor1Forward(speedVal);
  motor2Forward(speedVal);
  motor3Forward(speedVal);
  motor4Forward(speedVal);
}

// =====================================================
// ALL BACKWARD
// =====================================================

void allBackward(int speedVal) {

  motor1Backward(speedVal);
  motor2Backward(speedVal);
  motor3Backward(speedVal);
  motor4Backward(speedVal);
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
// STOP
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