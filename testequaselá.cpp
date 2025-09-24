/*
 * Robô seguidor de linha com 3 sensores + desvio de obstáculo
 * Sensores IR: Esquerda (4), Meio (7), Direita (2)
 * Ultrassônico: TRIG=13, ECHO=12
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

// --- ULTRASSÔNICO ---
#define TRIG 13
#define ECHO 12

// --- VELOCIDADES ---
const int VELOCIDADE = 80;        
const int VELOCIDADE_CURVA = 120;  
const int DISTANCIA_OBSTACULO = 20; // cm

// --- TEMPOS DA MANOBRA DE DESVIO (ms) ---
const int TEMPO_RE        = 400;
const int TEMPO_DIREITA   = 200;
const int TEMPO_FRENTE1   = 600;
const int TEMPO_ESQUERDA1 = 200;
const int TEMPO_FRENTE2   = 700;
const int TEMPO_ESQUERDA2 = 200;
const int TEMPO_FRENTE3   = 400;

// --- TEMPORIZADOR PARA PARADA ---
unsigned long tempoSemLinha = 0;
const unsigned long TEMPO_PARADA = 300; // 1 segundo

// === SETUP ===
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

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  Serial.println("Robô iniciado (Segue linha + Desvio)!");
}

// === LOOP PRINCIPAL ===
void loop() {
  long distancia = medirDistancia();

  if (distancia > 0 && distancia < DISTANCIA_OBSTACULO) {
    Serial.println("Obstáculo detectado! Executando manobra...");
    desviarObstaculo();
  } else {
    segueLinha();  // comportamento padrão
  }

  delay(10);
}

// === SEGUE LINHA COM PARADA DE 1S ===
void segueLinha() {
  int esq  = digitalRead(SENSOR_ESQ);
  int meio = digitalRead(SENSOR_MEIO);
  int dir  = digitalRead(SENSOR_DIR);

  Serial.print("E: "); Serial.print(esq);
  Serial.print(" | M: "); Serial.print(meio);
  Serial.print(" | D: "); Serial.println(dir);

  if (meio == HIGH && esq == LOW && dir == LOW) {
    frente();
    tempoSemLinha = 0; // reset temporizador
  }
  else if (esq == HIGH && meio == LOW && dir == LOW) {
    curva90Esq();
    tempoSemLinha = 0;
  }
  else if (dir == HIGH && meio == LOW && esq == LOW) {
    curva90Dir();
    tempoSemLinha = 0;
  }
  else if (esq == HIGH && meio == HIGH && dir == LOW) {
    esquerda();
    tempoSemLinha = 0;
  }
  else if (dir == HIGH && meio == HIGH && esq == LOW) {
    direita();
    tempoSemLinha = 0;
  }
  else if (esq == HIGH && meio == HIGH && dir == HIGH) {
    frente();
    tempoSemLinha = 0;
  }
  else {
    // Nenhum sensor ativo
    if (tempoSemLinha == 0) {
      tempoSemLinha = millis();
      frente(); // manter movimento inicial
    } else if (millis() - tempoSemLinha >= TEMPO_PARADA) {
      parar(); // parou após 1 segundo sem linha
    } else {
      frente(); // mantém movimento até atingir 1s
    }
  }
}

// === MANOBRA DE DESVIO ===
void desviarObstaculo() {
  parar(); delay(200);

  re();       delay(TEMPO_RE);        parar(); delay(200);
  direita();  delay(TEMPO_DIREITA);   parar(); delay(200);
  frente();   delay(TEMPO_FRENTE1);   parar(); delay(200);
  esquerda(); delay(TEMPO_ESQUERDA1); parar(); delay(200);
  frente();   delay(TEMPO_FRENTE2);   parar(); delay(200);
  esquerda(); delay(TEMPO_ESQUERDA2); parar(); delay(200);
  frente();   delay(TEMPO_FRENTE3);   parar(); delay(200);
}

// === FUNÇÕES DE MOVIMENTO ===
void frente() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, VELOCIDADE);
  analogWrite(ENB, VELOCIDADE);
}

void re() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
  analogWrite(ENA, VELOCIDADE_CURVA);
  analogWrite(ENB, VELOCIDADE_CURVA);
}

void direita() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  analogWrite(ENA, VELOCIDADE_CURVA);
  analogWrite(ENB, VELOCIDADE_CURVA);
}

void esquerda() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, VELOCIDADE_CURVA);
  analogWrite(ENB, VELOCIDADE_CURVA);
}

// === CURVAS 90° AUTOMÁTICAS ===
void curva90Esq() {
  while (digitalRead(SENSOR_MEIO) == LOW) {
    esquerda();
  }
  parar();
}

void curva90Dir() {
  while (digitalRead(SENSOR_MEIO) == LOW) {
    direita();
  }
  parar();
}

void parar() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

// === FUNÇÃO ULTRASSÔNICO ===
long medirDistancia() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duracao = pulseIn(ECHO, HIGH, 20000); // timeout 20ms
  long distancia = duracao * 0.034 / 2;
  return distancia;
}
