#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "YOUR_TEMPLATE_NAME"
#define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOKEN"
#include <PubSubClient.h>


#define MQTT_BROKER "192.168.57.145"      
#define MQTT_TOPIC "1-polutiondetection"  

#include <BlynkSimpleEsp8266.h>

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

// Isi dengan informasi WiFi Anda
char auth[] = "YOUR_AUTH_TOKEN";  // Ganti dengan Auth Token dari email Blynk
char ssid[] = "YOUR_WIFI_SSID";                               // Ganti dengan nama WiFi Anda
char pass[] = "YOUR_PASSWORD_WIFI";                        // Ganti dengan kata sandi WiFi Anda
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

SoftwareSerial NodeMCU(D4, D3);

void connectWifi() {
  Serial.print("Connecting to Wifi");
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("Wifi Connected");
}

void setup() {
  Serial.begin(115200);
  NodeMCU.begin(4800);
  pinMode(D4, INPUT);
  pinMode(D3, OUTPUT);
  Blynk.begin(auth, ssid, pass);
  // connect ke wifi
  connectWifi();

  // connect mqtt
  mqttClient.setServer(MQTT_BROKER, 1883);
  mqttClient.setCallback(callback);
}

char receivedData[256];

void loop() {
  Blynk.run();

  if (!mqttClient.connected()) reconnect();
  mqttClient.loop();

  if (NodeMCU.available() > 0) {
    int dataIndex = 0;

    while (NodeMCU.available()) {
      char character = NodeMCU.read();
      receivedData[dataIndex++] = character;

      // Cek apakah sudah mencapai batas maksimal array
      if (dataIndex >= sizeof(receivedData) - 1) {
        receivedData[dataIndex] = '\0';  // Pastikan menambahkan null terminator
        break;
      }
      delay(10);
    }

    receivedData[dataIndex] = '\0';  // Pastikan menambahkan null terminator di akhir data

    DynamicJsonDocument doc(2048);  // Ukuran buffer sesuaikan dengan kebutuhan
    DeserializationError error = deserializeJson(doc, receivedData);

    float gasValue = doc["Gas"];
    float humidityValue = doc["Hum"];
    float temperatureValue = doc["Temp"];
    char gasChar[12];
    char humidityChar[12];
    char temperatureChar[12];

    dtostrf(temperatureValue, 5, 2, temperatureChar);
    dtostrf(gasValue, 5, 2, gasChar);
    dtostrf(humidityValue, 5, 2, humidityChar);


    Serial.println(receivedData);

    // Melakukan pengecekan dan menuliskan nilai ke widget Blynk
    // ... (kode Anda untuk menulis ke widget Blynk)
    Blynk.virtualWrite(V0, humidityValue);
    Blynk.virtualWrite(V1, gasValue);
    Blynk.virtualWrite(V4, temperatureValue);
    if (gasValue > 200) {
      Blynk.virtualWrite(V2, "Polution Level : Bad!!");
      char StringResult[255];
      sprintf(StringResult, "Summary\nGas: %s\nHumidity: %s\nTemperature: %s\nResult : Polution lvl Bad!", gasChar, humidityChar, temperatureChar);
      Serial.println(StringResult);
      mqttClient.publish(MQTT_TOPIC, StringResult);
      Serial.println("Message published");
    } else {
      Blynk.virtualWrite(V2, "Polution Level : Good");
      char StringResult[255];
      sprintf(StringResult, "Summary\nGas: %s\nHumidity: %s\nTemperature: %s\nResult : Polution lvl Good", gasChar, humidityChar, temperatureChar);
      Serial.println(StringResult);
      mqttClient.publish(MQTT_TOPIC, StringResult);
      Serial.println("Message published");
    }

    // Memanggil fungsi untuk memeriksa polusi berdasarkan nilai sensor
    validatePolution(gasValue, humidityValue, temperatureValue);
  }

  delay(500);
}

void validatePolution(float gasVal, float humVal, float tempVal) {
  if (gasVal > 200 ) {
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


  } else {
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

// ini function buat nerima topic
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

// function buat reconnect ke mqtt server
void reconnect() {
  // Loop until we're reconnected
  while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (mqttClient.connect(clientId.c_str())) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}