/*
 * CÓDIGO ADEQUADO PARA 2 SENSORES
 * O robô anda para frente se o sensor da esquerda OU o da direita
 * detectar a linha preta. Caso contrário, ele para.
 */

// Definição dos pinos da Ponte H
#define ENA 3
#define ENB 5
#define IN1 6
#define IN2 9
#define IN3 10
#define IN4 11

// Definição dos pinos dos sensores IR (removido o sensor do meio)
#define SENSOR_ESQ 2
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

  // Sensores (configuração do sensor do meio removida)
  pinMode(SENSOR_ESQ, INPUT);
  pinMode(SENSOR_DIR, INPUT);

  Serial.begin(9600); // Para debug
}

// Função para andar para frente
void frente(int vel) {
  // Essa função não precisa de alterações
  analogWrite(ENA, vel);
  analogWrite(ENB, vel);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); // Corrigido para ambos os motores irem para frente
  digitalWrite(IN4, LOW);  // Assegurando que a roda esquerda também vá para frente
}

// Função para parar
void parar() {
  // Essa função não precisa de alterações
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void loop() {
  // Lê apenas os dois sensores restantes
  int esq = digitalRead(SENSOR_ESQ);
  int dir = digitalRead(SENSOR_DIR);

  // Debug no monitor serial (atualizado para dois sensores)
  Serial.print("Esq: "); Serial.print(esq);
  Serial.print("  Dir: "); Serial.println(dir);

  // Lógica de decisão atualizada para dois sensores
  // Agora "1" significa linha preta
  // Se o sensor da esquerda OU o da direita vir a linha, anda para frente.
  if (esq == 1 || dir == 1) {
    frente(velocidade);
  }  
  else {
    parar();
  }

  delay(10); // Adicionado um pequeno delay para estabilidade
}
