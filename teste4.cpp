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

const int VELOCIDADE = 180;

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
  // Leitura dos sensores
  int esq  = digitalRead(SENSOR_ESQ);
  int meio = digitalRead(SENSOR_MEIO);
  int dir  = digitalRead(SENSOR_DIR);

  Serial.print("E: "); Serial.print(esq);
  Serial.print(" | M: "); Serial.print(meio);
  Serial.print(" | D: "); Serial.println(dir);

  // === LÓGICA ===
  // HIGH = PRETO, LOW = BRANCO

  if (meio == HIGH && esq == LOW && dir == LOW) {
    frente();   // só meio = reto
  }
  else if (esq == HIGH && meio == LOW && dir == LOW) {
    esquerda(); // só esquerda = vira esquerda
  }
  else if (dir == HIGH && meio == LOW && esq == LOW) {
    direita();  // só direita = vira direita
  }
  else if (esq == HIGH && meio == HIGH && dir == LOW) {
    esquerda(); // meio + esquerda = corrige esquerda
  }
  else if (dir == HIGH && meio == HIGH && esq == LOW) {
    direita();  // meio + direita = corrige direita
  }
  else if (esq == HIGH && meio == HIGH && dir == HIGH) {
    frente();   // cruzamento = reto
  }
  else {
    parar();    // nenhum sensor vê preto = para
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
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, VELOCIDADE);
  analogWrite(ENB, VELOCIDADE);
}

void esquerda() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, VELOCIDADE);
  analogWrite(ENB, VELOCIDADE);
}

void parar() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
