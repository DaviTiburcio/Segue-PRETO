#define PINO_TRIG 13
#define PINO_ECHO 7

void setup() {
  Serial.begin(9600);
  Serial.println("--- Teste do Sensor Ultrassonico ---");

  pinMode(PINO_TRIG, OUTPUT);
  pinMode(PINO_ECHO, INPUT);
}

void loop() {
  long duracao;
  int distancia;

  digitalWrite(PINO_TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(PINO_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PINO_TRIG, LOW);

  duracao = pulseIn(PINO_ECHO, HIGH);

  distancia = duracao * 0.034 / 2;

  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  delay(500);
}
