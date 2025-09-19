// --- Pinagem dos sensores ---
const int IR1 = 2;  // Sensor IR esquerdo
const int IR2 = 7;  // Sensor IR direito

// --- Pinos do driver de motor ---
const int ENA = 3;   // PWM Motor A
const int ENB = 5;   // PWM Motor B
const int IN1 = 6;   // Motor A
const int IN2 = 9;   // Motor A
const int IN3 = 10;  // Motor B
const int IN4 = 11;  // Motor B

// --- Velocidade padrão ---
int velocidade = 255; // 0–255

void setup() {
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  analogWrite(ENA, velocidade);
  analogWrite(ENB, velocidade);
}

void loop() {
  // Leitura dos sensores (HIGH = branco, LOW = preto na maioria dos sensores)
  int s1 = digitalRead(IR1);
  int s2 = digitalRead(IR2);

  if (s1 == LOW && s2 == LOW) {
    // Ambos na linha preta → seguir reto
    frente();
  } 
  else if (s1 == LOW && s2 == HIGH) {
    // Esquerda detecta preto → corrija pra esquerda
    esquerda();
  } 
  else if (s1 == HIGH && s2 == LOW) {
    // Direita detecta preto → corrija pra direita
    direita();
  } 
  else {
    // Nenhum detecta preto → procurar linha
    parar();
    delay(200);
    // vira 90° pra direita
    direita90();
    delay(500);
    parar();
    delay(200);
    // verifica sensores de novo
    s1 = digitalRead(IR1);
    s2 = digitalRead(IR2);
    if (s1 == HIGH && s2 == HIGH) {
      // não achou, volta pro meio
      frente();
      delay(300);
      parar();
      delay(200);
      // tenta esquerda
      esquerda90();
      delay(500);
      parar();
    }
  }
}

// --- Funções de movimento ---
void frente() {
  analogWrite(ENA, velocidade);
  analogWrite(ENB, velocidade);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void parar() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void esquerda() {
  analogWrite(ENA, velocidade);
  analogWrite(ENB, velocidade);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void direita() {
  analogWrite(ENA, velocidade);
  analogWrite(ENB, velocidade);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void direita90() {
  analogWrite(ENA, velocidade);
  analogWrite(ENB, velocidade);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void esquerda90() {
  analogWrite(ENA, velocidade);
  analogWrite(ENB, velocidade);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
