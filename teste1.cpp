/********************************************************************
 * Código para Robô Seguidor de Linha com 4 Sensores IR
 * * Autor: Gemini (Google AI)
 * Data:  16 de Setembro de 2025
 * * Assume uma configuração com 4 sensores em linha e um driver L298N.
 * O robô segue uma linha preta em um fundo branco.
 ********************************************************************/

// --- CONFIGURAÇÃO DOS PINOS ---

// Pinos de controle para o Motor A (Esquerdo)
#define ENA 3 // Pino de velocidade (PWM)
#define IN1 6 // Pino de direção 1
#define IN2 9 // Pino de direção 2

// Pinos de controle para o Motor B (Direito)
#define ENB 5 // Pino de velocidade (PWM)
#define IN3 10  // Pino de direção 1
#define IN4 11 // Pino de direção 2

// Pinos dos 4 Sensores IR (da esquerda para a direita)
#define SENSOR_ESQUERDA_EXT 2 // Sensor 1 (Extrema Esquerda)
#define SENSOR_ESQUERDA_INT 4 // Sensor 2 (Interno Esquerda)
#define SENSOR_DIREITA_INT  7 // Sensor 3 (Interno Direita)
#define SENSOR_DIREITA_EXT  8 // Sensor 4 (Extrema Direita)

// --- CONFIGURAÇÃO DE VELOCIDADE ---
// Ajuste estes valores para calibrar o robô (0 a 255)
const int VELOCIDADE_BASE = 150; // Velocidade padrão para andar em frente
const int VELOCIDADE_CURVA = 180; // Velocidade para fazer as curvas

void setup() {
  // Inicia a comunicação serial para podermos ver o que o robô está "pensando"
  Serial.begin(9600);
  Serial.println("--- Robô Seguidor de Linha Iniciado ---");

  // Configura os pinos dos motores como SAÍDA
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Configura os pinos dos sensores como ENTRADA
  pinMode(SENSOR_ESQUERDA_EXT, INPUT);
  pinMode(SENSOR_ESQUERDA_INT, INPUT);
  pinMode(SENSOR_DIREITA_INT, INPUT);
  pinMode(SENSOR_DIREITA_EXT, INPUT);

  // Garante que o robô comece parado
  parar();
  
  Serial.println("Posicione o robô na linha. Iniciando em 3 segundos...");
  delay(3000); // Dá um tempo para você posicionar o robô
}

void loop() {
  // Lê o estado de cada sensor.
  // A maioria dos módulos retorna LOW (0) para branco e HIGH (1) para preto.
  // Se o seu for invertido, troque LOW por HIGH e HIGH por LOW nas condições abaixo.
  int s1 = digitalRead(SENSOR_ESQUERDA_EXT); // Esquerda Ext.
  int s2 = digitalRead(SENSOR_ESQUERDA_INT); // Esquerda Int.
  int s3 = digitalRead(SENSOR_DIREITA_INT);  // Direita Int.
  int s4 = digitalRead(SENSOR_DIREITA_EXT);  // Direita Ext.

  // Imprime os valores dos sensores no Monitor Serial para ajudar no debug
  // Formato: [S1, S2, S3, S4]
  Serial.print("Leituras: [");
  Serial.print(s1); Serial.print(", ");
  Serial.print(s2); Serial.print(", ");
  Serial.print(s3); Serial.print(", ");
  Serial.print(s4); Serial.println("]");


  // --- LÓGICA DE DECISÃO ---
  // A lógica é baseada na combinação de leituras dos sensores.
  // 0 = Branco, 1 = Preto

  // Caso 1: [0, 1, 1, 0] - Robô perfeitamente na linha, os 2 sensores do meio veem preto.
  if (!s1 && s2 && s3 && !s4) {
    Serial.println("Ação: EM FRENTE");
    moverFrente();
  }
  
  // Caso 2: [0, 0, 1, 0] ou [0, 0, 1, 1] - Robô desviou para a esquerda, precisa virar à DIREITA.
  else if ((!s1 && !s2 && s3 && !s4) || (!s1 && !s2 && s3 && s4)) {
    Serial.println("Ação: VIRAR DIREITA");
    virarDireita();
  }
  
  // Caso 3: [0, 1, 0, 0] ou [1, 1, 0, 0] - Robô desviou para a direita, precisa virar à ESQUERDA.
  else if ((!s1 && s2 && !s3 && !s4) || (s1 && s2 && !s3 && !s4)) {
    Serial.println("Ação: VIRAR ESQUERDA");
    virarEsquerda();
  }
  
  // Caso 4: [0, 0, 0, 1] - Curva acentuada para a DIREITA.
  else if (!s1 && !s2 && !s3 && s4) {
    Serial.println("Ação: VIRAR DIREITA (FORTE)");
    virarDireita();
  }

  // Caso 5: [1, 0, 0, 0] - Curva acentuada para a ESQUERDA.
  else if (s1 && !s2 && !s3 && !s4) {
    Serial.println("Ação: VIRAR ESQUERDA (FORTE)");
    virarEsquerda();
  }

  // Caso 6: [0, 0, 0, 0] - Robô perdeu a linha.
  else if (!s1 && !s2 && !s3 && !s4) {
    Serial.println("Ação: PARAR (linha perdida)");
    parar();
  }
  
  // Caso 7 (Opcional): [1, 1, 1, 1] - Cruzamento ou linha de chegada.
  else if (s1 && s2 && s3 && s4) {
    Serial.println("Ação: CRUZAMENTO (seguir em frente)");
    moverFrente(); 
  }
}

// --- FUNÇÕES DE MOVIMENTO ---

void moverFrente() {
  // Motor Esquerdo para frente
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  // Motor Direito para frente
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  // Define a velocidade
  analogWrite(ENA, VELOCIDADE_BASE);
  analogWrite(ENB, VELOCIDADE_BASE);
}

void virarDireita() {
  // Motor Esquerdo para frente, Motor Direito para trás (gira no próprio eixo)
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  // Define a velocidade da curva
  analogWrite(ENA, VELOCIDADE_CURVA);
  analogWrite(ENB, VELOCIDADE_CURVA);
}

void virarEsquerda() {
  // Motor Esquerdo para trás, Motor Direito para frente (gira no próprio eixo)
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  // Define a velocidade da curva
  analogWrite(ENA, VELOCIDADE_CURVA);
  analogWrite(ENB, VELOCIDADE_CURVA);
}

void parar() {
  // Desliga a energia dos motores
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
