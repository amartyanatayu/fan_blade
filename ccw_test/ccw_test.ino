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

void setup() {

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
}

void loop() {

  testMotor(AIN1_1, AIN2_1, PWMA_1, "Motor 1");
  testMotor(BIN1_1, BIN2_1, PWMB_1, "Motor 2");
  testMotor(AIN1_2, AIN2_2, PWMA_2, "Motor 3");
  testMotor(BIN1_2, BIN2_2, PWMB_2, "Motor 4");

  while (1);
}

void testMotor(int in1, int in2, int pwm, const char* name) {

  Serial.begin(115200);

  Serial.println(name);

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(pwm, 180);

  delay(3000);

  analogWrite(pwm, 0);

  delay(2000);
}