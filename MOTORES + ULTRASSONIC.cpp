#define ENA 5
#define IN1 7
#define IN2 6

#define ENB 2
#define IN3 4
#define IN4 3

#define TRIG_PIN 9
#define ECHO_PIN 8

const int VELOCIDADE_MAXIMA = 255;
const int DISTANCIA_OBSTACULO = 15;

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.begin(9600);
}

void loop() {
  long distancia = medirDistancia();

  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  if (distancia <= DISTANCIA_OBSTACULO && distancia > 0) {
    Serial.println("Obstaculo detectado! Desviando...");
    desviarObstaculo();
  } else {
    moverFrente();
  }

  delay(50);
}

void moverFrente() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  
  analogWrite(ENA, VELOCIDADE_MAXIMA);
  analogWrite(ENB, VELOCIDADE_MAXIMA);
}

void re() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  
  analogWrite(ENA, 180);
  analogWrite(ENB, 180);
}

void virarDireita() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
}

void parar() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void desviarObstaculo() {
  parar();
  delay(200);

  re();
  delay(500);

  parar();
  delay(200);
  
  virarDireita();
  delay(400);

  parar();
}

long medirDistancia() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  long duracao = pulseIn(ECHO_PIN, HIGH);
  
  long distancia = (duracao * 0.0343) / 2;
  
  return distancia;
}
