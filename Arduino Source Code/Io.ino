#include "FirebaseESP8266.h"
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "iot-example-87851-default-rtdb.firebaseio.com/" 
#define FIREBASE_AUTH "######################################"
#define WIFI_SSID "UpasaraSam"
#define WIFI_PASSWORD "************"

#define DHTPIN 2    // Connect data pin of DHT to D2
int led = D5;     // Connect LED to D5
int soil_sens = A0; //Connect data pin of Soil Moisture to A0
int ldr = A0; //Connect data pin of LDR to A0

#define DHTTYPE    DHT11
DHT dht(DHTPIN, DHTTYPE);

FirebaseData firebaseData;
FirebaseData ledData;

FirebaseJson json;


void setup()
{

  Serial.begin(9600);

  dht.begin();
  pinMode(led,OUTPUT);
  
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

}

void sensorUpdate(){
  float h = dht.readHumidity(); 
  float t = dht.readTemperature();
  float m = analogRead(soil_sens);
  float m = map(float m, 550,0,0,100);
  float s = analogRead(ldr);

  if (isnan(h) || isnan(t)|| isnan(m) || isnan(s){
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print(F("humidity: "));
  Serial.print(h);
  Serial.print(F("moisture: "));
  Serial.print(m);
  Serial.print(F("sunlight: "));
  Serial.print(s);
  Serial.print(F("%  temperature: "));
  Serial.print(t);
  Serial.print(F("°C  ,"));


  if (Firebase.setFloat(firebaseData, "/IrrigationSystem/temperature", t))
  {
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("Temperature sends");
    Serial.println();
  }
  else
  {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("Temperature not send");
    Serial.println();
  }

  if (Firebase.setFloat(firebaseData, "/IrrigationSystem/humidity", h))
  {
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("Humidity sends");
    Serial.println();
  }
  else
  {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("Humidity not send");
    Serial.println();
  }

  if (Firebase.setFloat(firebaseData, "/IrrigationSystem/moisture", m))
  {
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("Moisture sends");
    Serial.println();
  }
  else
  {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("Moisture not send");
    Serial.println();
  }
  if (Firebase.setFloat(firebaseData, "/IrrigationSystem/sunlight", s))
  {
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("Sunlight sends");
    Serial.println();
  }
  else
  {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("Sunlight not send");
    Serial.println();
  }
}
void loop() {
  sensorUpdate();
  
  if (Firebase.getString(ledData, "/IrrigationSystem/led")){
    Serial.println(ledData.stringData());
    if (ledData.stringData() == "1") {
    digitalWrite(led, HIGH);
    }
  else if (ledData.stringData() == "0"){
    digitalWrite(led, LOW);
    }
  }
  delay(100);
}
