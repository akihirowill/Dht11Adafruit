// INCLUSAO DE BIBLIOTECAS
#include <DHT.h>


// DEFINIÇÃO DE ENDEREÇOS
#define tipoSensor DHT11
#define pinSensor 7
#define DELAY_LEITURA 15000

// INSTANCIANDO OBJETOS
DHT sensorDHT(pinSensor, tipoSensor);

// DECLARACAO DE VARIAVEIS
float temperatura;
float umidade;
unsigned long ultimaLeitura;

void setup() {
  // INICIALIZACAO DO MONITOR SERIAL
  Serial.begin(9600); 

  // INICIALIZACAO DO SENSOR
  sensorDHT.begin();

  Serial.println("Fim setup()");
}

void loop() {
  if (millis() - ultimaLeitura > DELAY_LEITURA) {-
    // LEITURA DO SENSOR
    temperatura = sensorDHT.readTemperature();
    umidade = sensorDHT.readHumidity();

    // IMPRESSAO DOS DADOS COM RÓTULOS
    Serial.print("U:");
    Serial.println(umidade);
    Serial.print("T:");
    Serial.println(temperatura);
    
    ultimaLeitura = millis();
  }
}