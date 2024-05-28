
#include <ESP8266WiFi.h>
#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <Arduino.h>
#include <ESP8266SAM.h>
#include "AudioOutputI2SNoDAC.h"

#define BLYNK_TEMPLATE_ID "TMPLV3AimWq6"
#define BLYNK_DEVICE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "m1FzDzKCyGtdkaHdQbBM12P4qT2RwlMm"
char auth[] = "m1FzDzKCyGtdkaHdQbBM12P4qT2RwlMm";
char ssid[] = "Galaxya50"; //Enter your WIFI name
char pass[] = "vaish#@@"; //Enter your WIFI passowrd

AudioOutputI2SNoDAC *out = NULL;
BlynkTimer timer;
int smokeA0 = A0;
int sensorThres = 600;
int rainPin = D2;
int flame = D5;


  DHT dht(D4, DHT11);
WidgetTerminal terminal(V9);
ESP8266SAM *sam = new ESP8266SAM;
BLYNK_WRITE(V9)
{

  // if you type "Marco" into Terminal Widget - it will respond: "Polo:"
  if (String("hello") == param.asStr()) {
    terminal.println("hello") ;
    
  sam->Say(out, "hello");
  delay(5000);
  
  
  } 
  else if (String("how r u") == param.asStr()) {
    terminal.println("Fine") ;
    
  sam->Say(out, "fine");
  delay(5000);
  
  
  }

  // Ensure everything is sent
  terminal.flush();
}
  
void setup() {
  
  Serial.begin(115200);
  

  //Blynk.begin(auth, ssid, pass);

  Blynk.begin(auth, ssid, pass,"blynk.cloud", 8080);
  out = new AudioOutputI2SNoDAC();
  out->begin();

 
  dht.begin();
  pinMode(D2,INPUT);
//  timer.setInterval(1000L, sendSensor);
  pinMode(flame,INPUT);
  
 

  pinMode(smokeA0, INPUT);
  

}

/*
void sendSensor()

{  //dth11 sensor connected D3 pin

 
  float h = dht.readHumidity();
  float t = dht.readTemperature();
 
  Blynk.virtualWrite(V0, t);
  Serial.print("Humidity: ");
  Blynk.virtualWrite(V1, h);
  Serial.println(h);
 

  if (isnan(h) || isnan(t)) {

    Serial.println("Failed to read from DHT sensor!");

    return;

  }
  

}
*/
int flagf=0;
void notifyOnFire()
{

}

void notifyOnGasleakage()
{

  
  }
 

void loop() {
  Blynk.run();
 timer.run();
  float h = dht.readHumidity();
  float t = dht.readTemperature();
   Serial.print("Temperature: ");
  Serial.println(t);
  Blynk.virtualWrite(V5, t);
  Serial.print("Humidity: ");
  Blynk.virtualWrite(V6, h);
  Serial.println(h);



   int sensorReading = analogRead(A0);
  Serial.println("test");
  Serial.println(sensorReading);
  if(sensorReading > 350){
    Blynk.notify("Alert :Gas leakage");
    Serial.println("Gas leakage");
    sam->Say(out, "Gas leakage");
    delay(1000);
     sam->Say(out, "Gas leakage");
     delay(1000);
     delete sam;
    
   
}
  int rainState = digitalRead(rainPin);
  Serial.println("rain");
   Serial.println(rainState);
  
  
  
  if (rainState == 0 )
  {
    Blynk.notify("It's Raining outside!") ;
    Serial.println("It's Raining outside!");
   
    delay(100);
    
    
  }
  int flame_sensor  = digitalRead(flame);
  if (flame_sensor == 0)
    {
    
    Blynk.notify("Alert Fire Detected"); 
    sam->Say(out, "Fire");
    delay(1000);
     sam->Say(out, "Fire");
    
    }
  


}
