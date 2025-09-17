/*
 * CÓDIGO COMPLETO - Seguidor de Linha com 2 Sensores IR
 * Inclui as funções de controle dos motores no final do arquivo.
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
const int VELOCIDADE = 180; // Comece com uma velocidade menor para facilitar os testes

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

  Serial.println("Robô com 2 sensores pronto!");
}

void loop() {
  // Lê o estado de cada sensor. HIGH (1) = Preto, LOW (0) = Branco
  int estadoEsquerda = digitalRead(pinoSensorEsquerda);
  int estadoDireita  = digitalRead(pinoSensorDireita);

  Serial.print("Esquerda: ");
  Serial.print(estadoEsquerda);
  Serial.print(" | Direita: ");
  Serial.println(estadoDireita);

  // --- LÓGICA DE DECISÃO PARA 2 SENSORES ---

  // Se ambos veem BRANCO (0, 0), a linha está no meio. Vá para FRENTE.
  if (estadoEsquerda == LOW && estadoDireita == LOW) {
    frente();
  }
  // Se o sensor ESQUERDO vê PRETO (1, 0), o robô desviou para a direita. Vire à ESQUERDA.
  else if (estadoEsquerda == HIGH && estadoDireita == LOW) {
    esquerda();
  }
  // Se o sensor DIREITO vê PRETO (0, 1), o robô desviou para a esquerda. Vire à DIREITA.
  else if (estadoEsquerda == LOW && estadoDireita == HIGH) {
    direita();
  }
  // Se ambos veem PRETO (1, 1), é um cruzamento ou erro. PARE.
  else {
    parar();
  }
  
  delay(10); // Um delay pequeno é bom para estabilidade
}


// --- FUNÇÕES DE CONTROLE DOS MOTORES (ESTA PARTE ESTAVA FALTANDO) ---

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
