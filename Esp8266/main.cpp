#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

String sensorValue;

void setup() {

Serial.begin(9600);
WiFi.begin("HUAWEI-08F1","53218140");   //WiFi connection
while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
 
    delay(500);
    Serial.println("Waiting for connection");
 
  }
  Serial.println("Connected !");

}   

void loop() {     

if( WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
    if(Serial.available()){
        HTTPClient http;    //Declare object of class HTTPClient
        //sensorValue =  "34";
        String msg = Serial.readString();
        http.begin("http://192.168.8.200:5000/stream");      //Specify request destination
        http.addHeader("Content-Type", "application/json");  //Specify content-type header
        //String startmsg = "{\"sensorValue\":";
        //String endmsg = "}";
        //String msg = startmsg + sensorValue + endmsg;
        Serial.println(msg);
        int httpCode = http.POST(msg);
        Serial.println(httpCode);   //Send the request                 //Get the response payload
        http.end();  //Close connection
        delay(10);
    }
 
 }
 else
 {

    Serial.println("Error in WiFi connection");   
 
 }
 
  delay(30);  //Send a request every 30 seconds
 //Serial.print(Serial.readString());

}