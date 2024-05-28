#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>

#include <BlynkSimpleEsp8266.h>



const int trigPin1 = D6; 
const int trigPin2 = 1;
const int echoPin2 = D8;//D4
const int echoPin1 = D7;  //D3
int distance1;
long duration1;
int distance2;
long duration2;

 
#define ENA D0
#define IN1 D1
#define IN2 D2
#define IN3 D3
#define IN4 D4
#define ENB D5
 

long dur_f;
long dur_b;
long dur_l;
long dur_r;
long dur_pot;
int dist_f;
int dist_b;
int dist_l;
int dist_r;
int dist_pot;



bool forward = 0;
bool backward = 0;
bool left = 0;
bool right = 0;
int Speed;
#define BLYNK_TEMPLATE_ID "TMPLV3AimWq6"
#define BLYNK_DEVICE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "m1FzDzKCyGtdkaHdQbBM12P4qT2RwlMm"
char auth[] = "m1FzDzKCyGtdkaHdQbBM12P4qT2RwlMm"; //Enter your Blynk application auth token
char ssid[] = "Galaxya50"; //Enter your WIFI name
char pass[] = "vaish#@@"; //Enter your WIFI passowrd
BlynkTimer timer;
int d=0;
void setup() {
  

  pinMode(trigPin1, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin1, INPUT); // Sets the echoPin as an Input
//pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin2, INPUT); // Sets the echoPin as an Input

 
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass,"blynk.cloud", 8080);
  timer.setInterval(1L,Distance1);
 timer.setInterval(1L,Distance2);
 pinMode( A0, INPUT);
 
}

BLYNK_WRITE(V0) {
  forward = param.asInt();
}
 
BLYNK_WRITE(V1) {
  backward = param.asInt();
}
 
BLYNK_WRITE(V2) {
  left = param.asInt();
}
 
BLYNK_WRITE(V3) {
  right = param.asInt();
}
 
BLYNK_WRITE(V4) {
  Speed = param.asInt();
}


  
void Distance1(){

   digitalWrite(trigPin1, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin1, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin1, LOW);
duration2 = pulseIn(echoPin2, HIGH);

// Calculating the distance
distance2= duration2*0.034/2;

Serial.print("Distance2: ");
Serial.println(distance2);
}
void Distance2(){
digitalWrite(trigPin2, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin2, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin2, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration1 = pulseIn(echoPin1, HIGH);

// Calculating the distance
distance1= duration1*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance1: ");
Serial.println(distance1);
   digitalWrite(trigPin1, LOW);
delayMicroseconds(2);
}
// Sets the trigPin on HIGH state for 10 micro seconds

// Reads the echoPin, returns the sound wave travel time in microseconds


 

  
  
  


 
  

void loop() {



  
  Blynk.run();
  
  if (forward == 1 ) {
    carforward();
    Serial.println("carforward");
  } else if (backward == 1) {
    carbackward();
    Serial.println("carbackward");
    
  } else if (left == 1) {
    carturnleft();
    Serial.println("carfleft");
  } else if (right == 1) {
    carturnright();
    Serial.println("carright");
  } else if (forward == 0 && backward == 0 && left == 0 && right == 0) {
    carStop();
   // Serial.println("carstop");
  }
  if (forward == 0 && backward == 0 && left == 0 && right == 0){
  carStop();
  }
 
    timer.run();
int sensorReading = analogRead(A0);
Serial.println(sensorReading);
  delay(1000);
 

    
  /*
  digitalWrite(trig, HIGH);
 delayMicroseconds(10);
 digitalWrite(trig, LOW);


 dur_f = pulseIn(ef, HIGH);
 dur_b = pulseIn(eb, HIGH);
 dur_r = pulseIn(er, HIGH);
 dur_l = pulseIn(el, HIGH);
 dur_pot = pulseIn(epot, HIGH);

 dist_f= dur_f*0.034/2;
 dist_b= dur_b*0.034/2;
 dist_r= dur_r*0.034/2;
 dist_l= dur_l*0.034/2;
 dist_pot= dur_pot*0.034/2;


  digitalWrite(trig, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trig, HIGH);
delayMicroseconds(10);
digitalWrite(trig, LOW);
 duration = pulseIn(ef, HIGH);
 distance= duration*0.034/2;
 Serial.print("Distance: ");
Serial.println(distance);


 
*/


 
 
  
}

void carforward() {
 if(distance1 > 20){
    
  
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
 } 
  
  else{
 
   carStop();
    delay(2000);
    }
 
}

void carbackward(){
  if(distance1 > 20){
  
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
 } else{
  
   carStop();
   delay(2000); 
    }
 
} 
  
  

void carturnleft() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void carturnright() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void carStop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
