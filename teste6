/*
 * Robô seguidor de linha com 3 sensores
 * Sensores: Esquerda (4), Meio (7), Direita (2)
 * Lógica: HIGH = PRETO, LOW = BRANCO
 */

// --- PINOS DOS MOTORES ---
#define ENA 3  
#define IN1 5
#define IN2 6

#define ENB 11  
#define IN3 9
#define IN4 10

// --- PINOS DOS SENSORES IR ---
#define SENSOR_ESQ   4
#define SENSOR_MEIO  7
#define SENSOR_DIR   2

const int VELOCIDADE = 90;        // velocidade normal
const int VELOCIDADE_CURVA = 120;  // velocidade para curva 90°

void setup() {
  Serial.begin(9600);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(SENSOR_ESQ, INPUT);
  pinMode(SENSOR_MEIO, INPUT);
  pinMode(SENSOR_DIR, INPUT);

  Serial.println("Robô pronto para seguir a linha PRETA (HIGH = 1)!");
}

void loop() {
  int esq  = digitalRead(SENSOR_ESQ);
  int meio = digitalRead(SENSOR_MEIO);
  int dir  = digitalRead(SENSOR_DIR);

  Serial.print("E: "); Serial.print(esq);
  Serial.print(" | M: "); Serial.print(meio);
  Serial.print(" | D: "); Serial.println(dir);

  // === LÓGICA ===
  if (meio == HIGH && esq == LOW && dir == LOW) {
    frente();   // só meio = reto
  }
  else if (esq == HIGH && meio == LOW && dir == LOW) {
    curva90Esq(); // curva fechada para esquerda
  }
  else if (dir == HIGH && meio == LOW && esq == LOW) {
    curva90Dir(); // curva fechada para direita
  }
  else if (esq == HIGH && meio == HIGH && dir == LOW) {
    esquerda(); // meio + esquerda = correção leve esquerda
  }
  else if (dir == HIGH && meio == HIGH && esq == LOW) {
    direita();  // meio + direita = correção leve direita
  }
  else if (esq == HIGH && meio == HIGH && dir == HIGH) {
    frente();   // cruzamento = reto
  }
  else {
    parar();    // nenhum sensor = para
  }

  delay(10);
}

// === FUNÇÕES DE MOVIMENTO ===
void frente() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, VELOCIDADE);
  analogWrite(ENB, VELOCIDADE);
}

void direita() {
  // curva leve
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
  analogWrite(ENA, VELOCIDADE_CURVA);
  analogWrite(ENB, VELOCIDADE_CURVA);
}

void esquerda() {
  // curva leve
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
  analogWrite(ENA, VELOCIDADE_CURVA);
  analogWrite(ENB, VELOCIDADE_CURVA);0
}

void curva90Esq() {
  // gira no próprio eixo até o meio voltar a detectar preto
  while (digitalRead(SENSOR_MEIO) == LOW) {
    digitalWrite(IN1, 1);
    digitalWrite(IN2, 0);
    digitalWrite(IN3, 1);q
    digitalWrite(IN4, 0);
    analogWrite(ENA, VELOCIDADE_CURVA);
    analogWrite(ENB, VELOCIDADE_CURVA);
  }
  parar();
}

void curva90Dir() {
  // gira no próprio eixo até o meio voltar a detectar preto
  while (digitalRead(SENSOR_MEIO) == LOW) {
    digitalWrite(IN1, 0);
    digitalWrite(IN2, 1);
    digitalWrite(IN3, 0);
    digitalWrite(IN4, 1);
    analogWrite(ENA, VELOCIDADE_CURVA);
    analogWrite(ENB, VELOCIDADE_CURVA);
  }
  parar();
}

void parar() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
