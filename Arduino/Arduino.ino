#include <SoftwareSerial.h>
SoftwareSerial ArduinoUno(3,4);
float sensor = A0;


#include "DHT.h"
#define DHTPIN 2 
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup(){
	
	Serial.begin(115200);
	ArduinoUno.begin(4800);
   dht.begin();

}

void loop(){


  float gas_value = analogRead(sensor);
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  validatePolution(gas_value, humidity, temperature);
  // ArduinoUno.print("SUMMARY\nGas Value: " + String(gas_value) + " PPM\n");
  String jsonData = "{\"Gas\": " + String(gas_value) + ", \"Hum\": " + String(humidity) + ", \"Temp\": " + String(temperature) + "}";
  ArduinoUno.println(jsonData);


  delay(500);
}


void validatePolution(float gasVal, float humVal, float tempVal){
  if(gasVal > 200){
     Serial.println("SUMMARY");
    Serial.print(F("Gas Value : "));
    Serial.print(gasVal);
    Serial.println(" PPM");
   
    Serial.print(F("Humidity Value : "));
    Serial.print(humVal);
     Serial.println(" %");
    Serial.print(F("Temperature Value : "));
    Serial.print(tempVal);
    Serial.println(" °C");
    Serial.println("-----------------");
    Serial.println(F("Category Polution : Bad !!!"));
    Serial.println();

    
  }else{
     Serial.println("SUMMARY");
    Serial.print(F("Gas Value : "));
    Serial.print(gasVal);
    Serial.println(" PPM");
 
    Serial.print(F("Humidity Value : "));
    Serial.print(humVal);
     Serial.println(" %");
    Serial.print(F("Temperature Value : "));
    Serial.print(tempVal);
    Serial.println(" °C");
    Serial.println("-----------------");
    Serial.println(F("Category Polution : Good"));
    Serial.println();
  }
}