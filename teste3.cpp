/*
 * CÓDIGO CORRIGIDO - Lógica Invertida
 * Agora o robô seguirá a linha PRETA.
 */

// --- PINOS DOS MOTORES (do SEU código que funcionou) ---
#define ENA 3  // Pino de velocidade do Motor A (Direita)
#define IN1 6
#define IN2 9

#define ENB 5  // Pino de velocidade do Motor B (Esquerda)
#define IN3 10
#define IN4 11

// --- PINOS DOS SENSORES IR ---
#define pinoSensorEsquerda 2
#define pinoSensorDireita  7

// Velocidade dos motores (0 = parado, 255 = máximo)
const int VELOCIDADE = 180; 

void setup() {
  Serial.begin(9600);

  // Configura os pinos dos motores como SAÍDA
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Configura os pinos dos sensores como ENTRADA
  pinMode(pinoSensorEsquerda, INPUT);
  pinMode(pinoSensorDireita, INPUT);

  Serial.println("Robô pronto para seguir o PRETO!");
}

void loop() {
  // Lê o estado de cada sensor.
  // No seu sensor: LOW (0) = Preto, HIGH (1) = Branco
  int estadoEsquerda = digitalRead(pinoSensorEsquerda);
  int estadoDireita  = digitalRead(pinoSensorDireita);

  Serial.print("Esquerda: ");
  Serial.print(estadoEsquerda);
  Serial.print(" | Direita: ");
  Serial.println(estadoDireita);

  // --- LÓGICA DE DECISÃO CORRIGIDA ---

  // Se ambos veem BRANCO (HIGH, HIGH), a linha preta está no meio. Vá para FRENTE.
  if (estadoEsquerda == HIGH && estadoDireita == HIGH) {
    frente();
  }
  // Se o sensor ESQUERDO vê PRETO (LOW, HIGH), o robô desviou para a direita. Vire à ESQUERDA.
  else if (estadoEsquerda == LOW && estadoDireita == HIGH) {
    esquerda();
  }
  // Se o sensor DIREITO vê PRETO (HIGH, LOW), o robô desviou para a esquerda. Vire à DIREITA.
  else if (estadoEsquerda == HIGH && estadoDireita == LOW) {
    direita();
  }
  // Se ambos veem PRETO (LOW, LOW), é um cruzamento ou erro. PARE.
  else {
    parar();
  }
  
  delay(10);
}


// --- FUNÇÕES DE CONTROLE DOS MOTORES (Não mudam) ---

void frente() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
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
