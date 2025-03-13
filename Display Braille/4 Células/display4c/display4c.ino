#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(&Wire, 0x40);Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(&Wire, 0x41);

#define SERVOMIN  205 // Pulso mínimo (~1ms)
#define SERVOMAX  409 // Pulso máximo (~2ms)

void setup() {
  Serial.begin(9600);
  Serial.println("16 channel PWM test!");
  pwm1.begin(); pwm1.setPWMFreq(50);  //Inicia e define a frequência típica para servos (50 Hz)
  pwm2.begin(); pwm2.setPWMFreq(50);  //Inicia e define a frequência típica para servos (50 Hz)
}

void analisarCaractereC1(char inputChar) {
  // Move os servos de acordo com o caractere recebido
  pwm1.setPWM(0, 0, SERVOMIN);
  pwm1.setPWM(1, 0, SERVOMIN);
  pwm1.setPWM(2, 0, SERVOMIN);
  pwm1.setPWM(3, 0, SERVOMIN);
  pwm1.setPWM(4, 0, SERVOMIN);
  pwm1.setPWM(5, 0, SERVOMIN);

  if (strchr("abcdefghklmnopqruvxyz12345678", inputChar)) {
    pwm1.setPWM(0, 0, SERVOMAX);
    Serial.print("s1");
  }
  if (strchr("bfghijlpqrstvw026789", inputChar)) {
    pwm1.setPWM(1, 0, SERVOMAX);
    Serial.print("s2");
  }
  if (strchr("klmnopqrstuvxyz", inputChar)) {
    pwm1.setPWM(2, 0, SERVOMAX);
    Serial.print("s3");
  }
  if (strchr("cdfgijmnpqstwxy034679", inputChar)) {
    pwm1.setPWM(3, 0, SERVOMAX);
    Serial.print("s4");
  }
  if (strchr("deghjnoqrtwyz04578", inputChar)) {
    pwm1.setPWM(4, 0, SERVOMAX);
    Serial.print("s5");
  }
  if (strchr("uvwxyz", inputChar)) {
    pwm1.setPWM(5, 0, SERVOMAX);
    Serial.print("s6");
  }

  // Mantém os servos na posição por 1.5 segundos
  delay(1500);

  // Retorna todos os servos à posição baixa
  pwm1.setPWM(0, 0, SERVOMIN);
  pwm1.setPWM(1, 0, SERVOMIN);
  pwm1.setPWM(2, 0, SERVOMIN);
  pwm1.setPWM(3, 0, SERVOMIN);
  pwm1.setPWM(4, 0, SERVOMIN);
  pwm1.setPWM(5, 0, SERVOMIN);
  delay(500);
}

void identificarNumeroC1() {
  pwm1.setPWM(0, 0, SERVOMAX);
  pwm1.setPWM(1, 0, SERVOMAX);
  pwm1.setPWM(2, 0, SERVOMAX);
  pwm1.setPWM(5, 0, SERVOMAX);
  delay(1500);
  pwm1.setPWM(0, 0, SERVOMIN);
  pwm1.setPWM(1, 0, SERVOMIN);
  pwm1.setPWM(2, 0, SERVOMIN);
  pwm1.setPWM(5, 0, SERVOMIN);
  delay(500);
}

void analisarCaractereC2(char inputChar) {
  // Move os servos de acordo com o caractere recebido
  pwm1.setPWM(6, 0, SERVOMIN);
  pwm1.setPWM(7, 0, SERVOMIN);
  pwm1.setPWM(8, 0, SERVOMIN);
  pwm1.setPWM(9, 0, SERVOMIN);
  pwm1.setPWM(10, 0, SERVOMIN);
  pwm1.setPWM(11, 0, SERVOMIN);

  if (strchr("abcdefghklmnopqruvxyz12345678", inputChar)) {
    pwm1.setPWM(6, 0, SERVOMAX);
    Serial.print("s1");
  }
  if (strchr("bfghijlpqrstvw026789", inputChar)) {
    pwm1.setPWM(7, 0, SERVOMAX);
    Serial.print("s2");
  }
  if (strchr("klmnopqrstuvxyz", inputChar)) {
    pwm1.setPWM(8, 0, SERVOMAX);
    Serial.print("s3");
  }
  if (strchr("cdfgijmnpqstwxy034679", inputChar)) {
    pwm1.setPWM(9, 0, SERVOMAX);
    Serial.print("s4");
  }
  if (strchr("deghjnoqrtwyz04578", inputChar)) {
    pwm1.setPWM(10, 0, SERVOMAX);
    Serial.print("s5");
  }
  if (strchr("uvwxyz", inputChar)) {
    pwm1.setPWM(11, 0, SERVOMAX);
    Serial.print("s6");
  }

  // Mantém os servos na posição por 1.5 segundos
  delay(1500);

  // Retorna todos os servos à posição baixa
  pwm1.setPWM(6, 0, SERVOMIN);
  pwm1.setPWM(7, 0, SERVOMIN);
  pwm1.setPWM(8, 0, SERVOMIN);
  pwm1.setPWM(9, 0, SERVOMIN);
  pwm1.setPWM(10, 0, SERVOMIN);
  pwm1.setPWM(11, 0, SERVOMIN);
  delay(500);
}

void identificarNumeroC2() {
  pwm1.setPWM(6, 0, SERVOMAX);
  pwm1.setPWM(7, 0, SERVOMAX);
  pwm1.setPWM(8, 0, SERVOMAX);
  pwm1.setPWM(11, 0, SERVOMAX);
  delay(1500);
  pwm1.setPWM(6, 0, SERVOMIN);
  pwm1.setPWM(7, 0, SERVOMIN);
  pwm1.setPWM(8, 0, SERVOMIN);
  pwm1.setPWM(11, 0, SERVOMIN);
  delay(500);
}

void loop() {
    static bool viuNumero = false; // Flag para indicar se os servos foram acionados para número

    if (Serial.available() > 0) {
        // Lê a palavra da serial
        String inputString = Serial.readString();

        // Percorre a string de forma sequencial
        for (int i = 0; i < inputString.length(); i++) {
            char inputChar = inputString.charAt(i);

            // Alterna entre os dois processamentos
            if (i % 2 == 0) { // Índice par (C1)
                if (isdigit(inputChar) && !viuNumero) {
                    identificarNumeroC1();
                    viuNumero = true;
                }
                analisarCaractereC1(inputChar);
            } else { // Índice ímpar (C2)
                if (isdigit(inputChar) && !viuNumero) {
                    identificarNumeroC2();
                    viuNumero = true;
                }
                analisarCaractereC2(inputChar);
            }
        }

        // Reseta a flag após processar toda a string
        viuNumero = false;
    }
}

