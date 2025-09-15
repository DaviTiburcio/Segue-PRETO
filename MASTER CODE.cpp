const int SENSOR_PINS[] = {A0, A1, A2, A3};
const int NUM_SENSORS = sizeof(SENSOR_PINS) / sizeof(int);
const int ENA = 5, IN1 = 4, IN2 = 3;
const int ENB = 6, IN3 = 8, IN4 = 7;
const int LED_PIN = 13;

const int CALIBRATION_TIME = 5000;
unsigned int sensorMin[NUM_SENSORS];
unsigned int sensorMax[NUM_SENSORS];

const int LINE_THRESHOLD = 300;
const int CENTER_POSITION = (NUM_SENSORS - 1) * 1000 / 2;

float Kp = 0.1;
float Ki = 0.0001;
float Kd = 4.0;

int MAX_SPEED = 220;
int CRUISE_SPEED = 160;
int TURN_SPEED = 100;

float error = 0;
float lastError = 0;
float integral = 0;
const float INTEGRAL_LIMIT = 3000;

void setup() {
  Serial.begin(115200);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  delay(1000);
  calibrateSensors();
}

void loop() {
  error = readLinePosition();
  integral += error;
  integral = constrain(integral, -INTEGRAL_LIMIT, INTEGRAL_LIMIT);
  float derivative = error - lastError;
  float correction = (Kp * error) + (Ki * integral) + (Kd * derivative);
  lastError = error;
  int currentSpeed = map(abs(error), 0, CENTER_POSITION, MAX_SPEED, TURN_SPEED);
  currentSpeed = constrain(currentSpeed, TURN_SPEED, MAX_SPEED);
  setMotorSpeeds(currentSpeed, correction);
}

void calibrateSensors() {
  digitalWrite(LED_PIN, HIGH);
  for (int i = 0; i < NUM_SENSORS; i++) {
    sensorMin[i] = 1023;
    sensorMax[i] = 0;
  }
  long startTime = millis();
  while (millis() - startTime < CALIBRATION_TIME) {
    for (int i = 0; i < NUM_SENSORS; i++) {
      int reading = analogRead(SENSOR_PINS[i]);
      if (reading < sensorMin[i]) sensorMin[i] = reading;
      if (reading > sensorMax[i]) sensorMax[i] = reading;
    }
  }
  digitalWrite(LED_PIN, LOW);
}

float readLinePosition() {
  float average = 0;
  float sum = 0;
  bool lineDetected = false;
  for (int i = 0; i < NUM_SENSORS; i++) {
    int rawValue = analogRead(SENSOR_PINS[i]);
    unsigned int calibratedValue = map(rawValue, sensorMin[i], sensorMax[i], 0, 1000);
    if (calibratedValue > LINE_THRESHOLD) {
      lineDetected = true;
    }
    average += (float)calibratedValue * (i * 1000);
    sum += calibratedValue;
  }
  if (!lineDetected) {
    if (lastError > (CENTER_POSITION / 2)) return CENTER_POSITION;
    else if (lastError < -(CENTER_POSITION / 2)) return -CENTER_POSITION;
    else return 0;
  }
  return (average / sum) - CENTER_POSITION;
}

void setMotorSpeeds(int base_speed, float correction) {
  int leftSpeed = base_speed - correction;
  int rightSpeed = base_speed + correction;
  if (leftSpeed >= 0) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, constrain(leftSpeed, 0, 255));
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(ENA, constrain(abs(leftSpeed), 0, 255));
  }
  if (rightSpeed >= 0) {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, constrain(rightSpeed, 0, 255));
  } else {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENB, constrain(abs(rightSpeed), 0, 255));
  }
}
