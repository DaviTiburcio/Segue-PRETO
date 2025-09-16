// Definição dos pinos da Ponte H
#define ENA 3
#define ENB 5
#define IN1 6
#define IN2 9
#define IN3 10
#define IN4 11

// Definição dos pinos dos sensores IR
#define SENSOR_ESQ 2
#define SENSOR_MEIO 4
#define SENSOR_DIR 7

// Velocidade base dos motores (0-255)
int velocidade = 180;

void setup() {
  // Motores
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Sensores
  pinMode(SENSOR_ESQ, INPUT);
  pinMode(SENSOR_MEIO, INPUT);
  pinMode(SENSOR_DIR, INPUT);

  Serial.begin(9600); // Para debug
}

// Função para andar para frente
void frente(int vel) {
  analogWrite(ENA, vel);
  analogWrite(ENB, vel);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// Função para parar
void parar() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void loop() {
  // Lê sensores
  int esq = digitalRead(SENSOR_ESQ);
  int meio = digitalRead(SENSOR_MEIO);
  int dir = digitalRead(SENSOR_DIR);

  // Debug no monitor serial (opcional)
  Serial.print("Esq: "); Serial.print(esq);
  Serial.print("  Meio: "); Serial.print(meio);
  Serial.print("  Dir: "); Serial.println(dir);

  // Agora "1" significa linha preta
  if (esq == 1 || meio == 1 || dir == 1) {
    frente(velocidade);
  } 
  else {
    parar();
  }
}
