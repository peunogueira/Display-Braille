#include <ESP32Servo.h>

// Definição dos pinos dos servomotores
const int servo1Pin = 5;
const int servo2Pin = 19;
const int servo3Pin = 16;
const int servo4Pin = 12;
const int servo5Pin = 27;
const int servo6Pin = 25;
const int buzzerPin = 14; // Pino do buzzer

// Criação dos objetos Servo
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

// Posições dos servos
const int posicaoAltaD = 70;
const int posicaoBaixaD = 0;

void setup() {
  // Anexa os servos aos pinos
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
  servo3.attach(servo3Pin);
  servo4.attach(servo4Pin);
  servo5.attach(servo5Pin);
  servo6.attach(servo6Pin);

  // Pino do buzzer
  pinMode(buzzerPin, OUTPUT);

  // Inicializa a comunicação serial
  Serial.begin(115200);
}

// Função para analisar um caractere e controlar os servos
void analisarCaractere(char inputChar) {
  // Move os servos de acordo com o caractere recebido
  servo1.write(posicaoBaixa);
  servo2.write(posicaoBaixa);
  servo3.write(posicaoBaixa);
  servo4.write(posicaoBaixa);
  servo5.write(posicaoBaixa);
  servo6.write(posicaoBaixa);

  if (strchr("abcdefghklmnopqruvxyz12345678", inputChar)) {
    servo1.write(posicaoAlta);
    Serial.print("s1");
  }
  if (strchr("bfghijlpqrstvw026789", inputChar)) {
    servo2.write(posicaoAlta);
    Serial.print("s2");
  }
  if (strchr("klmnopqrstuvxyz", inputChar)) {
    servo3.write(posicaoAlta);
    Serial.print("s3");
  }
  if (strchr("cdfgijmnpqstwxy034679", inputChar)) {
    servo4.write(posicaoAlta);
    Serial.print("s4");
  }
  if (strchr("deghjnoqrtwyz04578", inputChar)) {
    servo5.write(posicaoAlta);
    Serial.print("s5");
  }
  if (strchr("uvwxyz", inputChar)) {
    servo6.write(posicaoAlta);
    Serial.print("s6");
  }

  // Mantém os servos na posição por 1.5 segundos
  delay(1500);

  // Retorna todos os servos à posição baixa
  servo1.write(posicaoBaixa);
  servo2.write(posicaoBaixa);
  servo3.write(posicaoBaixa);
  servo4.write(posicaoBaixa);
  servo5.write(posicaoBaixa);
  servo6.write(posicaoBaixa);
  delay(500);
}

void tocarBuzzer() {
  tone(buzzerPin, 500); 
  delay(500);            
  noTone(buzzerPin);    
}

void identificarNumero() {
  servo1.write(posicaoAlta);
  servo2.write(posicaoAlta);
  servo3.write(posicaoAlta);
  servo4.write(posicaoAlta);
  delay(1500);
  servo1.write(posicaoBaixa);
  servo2.write(posicaoBaixa);
  servo3.write(posicaoBaixa);
  servo4.write(posicaoBaixa);
  delay(500);
}

void loop() {
  static bool viuNumero = false; // Flag para indicar se os servos foram acionados para número

  if (Serial.available() > 0) {
    // Lê a palavra da serial
    String inputString = Serial.readString();
    
    for (int i = 0; i < inputString.length(); i++) {
      char inputChar = inputString.charAt(i);

      // Verifica se é um número e se a flag ainda está false
      if (isdigit(inputChar) && !viuNumero) {
        identificarNumero();
        viuNumero = true;  // Define a flag para indicar que identificou um número
      }

      // Analisar cada caractere da string
      analisarCaractere(inputChar);
    }

    tocarBuzzer();  

    // Reseta a flag após processar toda a string
    viuNumero = false;
  }
}
