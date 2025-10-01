#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

// Definição dos pinos do driver L298N
const int motorIn1 = 19;  // Motor Esquerdo
const int motorIn2 = 21;
const int motorIn3 = 22;  // Motor Direito
const int motorIn4 = 23;

int valSpeed = 255; // Velocidade inicial (0–255)

// Funções de movimento
// "F" = trás e "B" = frente (inversão solicitada)
void frente() {
  analogWrite(motorIn1, 0);
  analogWrite(motorIn2, valSpeed);
  analogWrite(motorIn3, 0);
  analogWrite(motorIn4, valSpeed);
}

void tras() {
  analogWrite(motorIn1, valSpeed);
  analogWrite(motorIn2, 0);
  analogWrite(motorIn3, valSpeed);
  analogWrite(motorIn4, 0);
}

void esquerda() {
  analogWrite(motorIn1, 0);
  analogWrite(motorIn2, valSpeed);
  analogWrite(motorIn3, valSpeed);
  analogWrite(motorIn4, 0);
}

void direita() {
  analogWrite(motorIn1, valSpeed);
  analogWrite(motorIn2, 0);
  analogWrite(motorIn3, 0);
  analogWrite(motorIn4, valSpeed);
}

void parar() {
  analogWrite(motorIn1, 0);
  analogWrite(motorIn2, 0);
  analogWrite(motorIn3, 0);
  analogWrite(motorIn4, 0);
}

void setup() {
  Serial.begin(115200);

  pinMode(motorIn1, OUTPUT);
  pinMode(motorIn2, OUTPUT);
  pinMode(motorIn3, OUTPUT);
  pinMode(motorIn4, OUTPUT);

  parar(); // começa parado

  // Inicia Bluetooth
  if (!SerialBT.begin("CarrinhoESP32")) {
    Serial.println("Erro ao iniciar Bluetooth!");
    while (true);
  }
  Serial.println("Bluetooth iniciado. Procure por 'CarrinhoESP32'.");
}

void loop() {
  // Processa comandos Bluetooth
  if (SerialBT.available()) {
    char command = SerialBT.read();
    Serial.println(command);

    switch (command) {
      case 'F': frente(); break;   // AGORA É TRÁS
      case 'B': tras(); break;     // AGORA É FRENTE
      case 'L': esquerda(); break;
      case 'R': direita(); break;
      case 'S': parar(); break;

      case '0': valSpeed = 0; break;
      case '1': valSpeed = 25; break;
      case '2': valSpeed = 50; break;
      case '3': valSpeed = 75; break;
      case '4': valSpeed = 100; break;
      case '5': valSpeed = 125; break;
      case '6': valSpeed = 150; break;
      case '7': valSpeed = 175; break;
      case '8': valSpeed = 200; break;
      case '9': valSpeed = 255; break;
    }
  }
}
