#include <Arduino.h>
#include <DHT.h>

#define BAUDRATE 115200   //Taxa da comunicação Serial da ESP (bits por segundo)

#define DHTPIN 4          //Porta do sensor na ESP
#define DHTMODEL DHT11    //Tipo do DHT(pode ser DHT22)

DHT dht(DHTPIN, DHTMODEL);  //Definição do DHT

void setup() 
{
  Serial.begin(BAUDRATE);
  Serial.println(F("Iniciando leitura de Umidade e Temperatura..."));
  dht.begin();
}

void loop() 
{
  float humidity = dht.readHumidity();          //Leitura da umidade
  float temperature = dht.readTemperature();    //Leitura da temperatura

  if(isnan(humidity) || isnan(temperature))
  {
    Serial.println("ERRO na leitura");          //Tratamento de erro caso não retorne um número
  }

  else                                          //Print para Script python criar o CSV
  {
    Serial.print(humidity);
    Serial.print(",");
    Serial.println(temperature);
  }

  delay(2000);
}
