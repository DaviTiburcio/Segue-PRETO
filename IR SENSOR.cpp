#define SENSOR_1_PIN  2
#define SENSOR_2_PIN  3
#define SENSOR_3_PIN  4
#define SENSOR_4_PIN  5

void setup() {
  Serial.begin(9600);
  Serial.println("--- Teste dos Sensores IR ---");
  Serial.println("Aproxime uma superficie preta de cada sensor.");

  pinMode(SENSOR_1_PIN, INPUT);
  pinMode(SENSOR_2_PIN, INPUT);
  pinMode(SENSOR_3_PIN, INPUT);
  pinMode(SENSOR_4_PIN, INPUT);
}

void loop() {
  int estadoSensor1 = digitalRead(SENSOR_1_PIN);
  int estadoSensor2 = digitalRead(SENSOR_2_PIN);
  int estadoSensor3 = digitalRead(SENSOR_3_PIN);
  int estadoSensor4 = digitalRead(SENSOR_4_PIN);

  Serial.print("Valores: [S1:");
  Serial.print(estadoSensor1);
  Serial.print(", S2:");
  Serial.print(estadoSensor2);
  Serial.print(", S3:");
  Serial.print(estadoSensor3);
  Serial.print(", S4:");
  Serial.print(estadoSensor4);
  Serial.println("]");

  if (estadoSensor1 == HIGH) {
    Serial.println(">>> Sensor 1 detectou NEGROS NIGGAS!");
  }
  if (estadoSensor2 == HIGH) {
    Serial.println(">>> Sensor 2 detectou NEGROS NIGGAS!");
  }
  if (estadoSensor3 == HIGH) {
    Serial.println(">>> Sensor 3 detectou NEGROS NIGGAS!");
  }
  if (estadoSensor4 == HIGH) {
    Serial.println(">>> Sensor 4 detectou NEGROS NIGGAS!");
  }

  Serial.println("---------------------------------");

  delay(500);
}
