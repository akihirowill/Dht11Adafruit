// INCLUINDO BIBLIOTECAS
#include "config.h"

//INSTANCIANDO OBJETOS DO FEED
AdafruitIO_Feed *temperaturaFeed = io.feed("temperatura");
AdafruitIO_Feed *umidadeFeed = io.feed("umidade");

// Variáveis globais para armazenar os dados recebidos
String inputString = "";         // String para armazenar os dados recebidos
bool stringCompleta = false;     // Flag para indicar que a string está completa

void setup() {
  Serial.begin(9600);

  // Conecte-se ao Adafruit IO
  io.connect();

  // Aguarde a conexão
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("Conectado ao Adafruit IO");

  // Inicializa a string de entrada
  inputString.reserve(200);
}

void loop() {
  io.run();

  // Processa os dados recebidos quando a string está completa
  if (stringCompleta) {
    processaString();
    inputString = ""; // Limpa a string de entrada
    stringCompleta = false; // Reseta a flag
  }
}

void serialEvent() {
  // Lê os dados da porta serial
  while (Serial.available()) {
    char inChar = (char)Serial.read(); // Lê um caractere da porta serial
    inputString += inChar; // Adiciona o caractere à string de entrada
    if (inChar == '\n') { // Verifica se o caractere é uma nova linha
      stringCompleta = true; // Define a flag indicando que a string está completa
    }
  }
}

void processaString() {
  // Verifica se a string começa com "T:" ou "U:"
  if (inputString.startsWith("T:") || inputString.startsWith("U:")) {
    int indexT = inputString.indexOf("T:"); // Encontra a posição de "T:"
    int indexU = inputString.indexOf("U:"); // Encontra a posição de "U:"

    // Verifica se "T:" está presente na string
    if (indexT != -1) {
      int endIndex = inputString.indexOf(' ', indexT);
      if (endIndex == -1) endIndex = inputString.length();
      String tempStr = inputString.substring(indexT + 2, endIndex);
      tempStr.trim();
      float temperatura = tempStr.toFloat();

      // Imprime o valor de temperatura recebido no monitor serial
      Serial.print("Temperatura recebida: ");
      Serial.println(temperatura);

      // Envia o valor de temperatura para o Adafruit IO
      temperaturaFeed->save(temperatura);
    }

    // Verifica se "U:" está presente na string
    if (indexU != -1) {
      int endIndex = inputString.indexOf(' ', indexU);
      if (endIndex == -1) endIndex = inputString.length();
      String humStr = inputString.substring(indexU + 2, endIndex);
      humStr.trim();
      float umidade = humStr.toFloat();

      // Imprime o valor de umidade recebido no monitor serial
      Serial.print("Umidade recebida: ");
      Serial.println(umidade);

      // Envia o valor de umidade para o Adafruit IO
      umidadeFeed->save(umidade);
    }
  }
}