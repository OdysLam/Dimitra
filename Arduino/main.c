#include <ArduinoJson.h>
#include <DHT.h>
#include <DHT_U.h>
#include <SoftwareSerial.h>



DHT dht(5,DHT11);
SoftwareSerial mySerial(10, 11); // RX, TX


const int pResistor = A2;

int sensorValue = 0;
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(pResistor, INPUT);
  
  
}

// the loop routine runs over and over again forever:
void loop() {
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& packet = jsonBuffer.createObject();
    float temp = dht.readTemperature();
    float hum = dht.readHumidity();
    int water = analogRead(A0);
    int light = analogRead(A1);
    water = map(water,0,670,0,20);
    light = map(light,0,1000,0,100);
    packet["temperature"] = temp;
    packet["humidity"] = hum;
    packet["water"] = water;
    packet["light"] = light;
    char strPacket[100];
    packet.printTo(strPacket);
    mySerial.write(strPacket);
    Serial.println(strPacket);
    delay(5000);
  
} 
