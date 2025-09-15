#define ENA  6
#define IN1  2
#define IN2  3

#define ENB  9
#define IN3  4
#define IN4  5

#define VELOCIDADE_VIRADA 200
#define DURACAO_VIRADA_MS 500

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600);
  Serial.println("Iniciando a sequencia do retangulo...");
}

void loop() {
  Serial.println("Passo 1: Frente por 4 segundos.");
  moverParaFrente(255);
  delay(4000);

  Serial.println("Passo 2: Virando a direita.");
  virarDireita();
  delay(200);

  Serial.println("Passo 3: Frente por 3 segundos.");
  moverParaFrente(255);
  delay(3000);

  Serial.println("Passo 4: Virando a direita.");
  virarDireita();
  delay(200);

  Serial.println("Passo 5: Frente por 4 segundos.");
  moverParaFrente(255);
  delay(4000);

  Serial.println("Passo 6: Virando a direita.");
  virarDireita();
  delay(200);

  Serial.println("Passo 7: Frente por 3 segundos.");
  moverParaFrente(255);
  delay(3000);

  Serial.println("FIM: Sequencia finalizada. Parando os motores.");
  pararMotores();

  while (true) {
  }
}

void moverParaFrente(int velocidade) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, velocidade);
  
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, velocidade);
}

void virarDireita() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, VELOCIDADE_VIRADA);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, VELOCIDADE_VIRADA);
  
  delay(DURACAO_VIRADA_MS);
}

void pararMotores() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
