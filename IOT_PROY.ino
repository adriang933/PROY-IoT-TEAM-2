#include "UbidotsEsp32Mqtt.h"
#define MOTOR_IN1 4
#define MOTOR_IN2 2   
const char *UBIDOTS_TOKEN = "BBFF-BSGQqMO7UC03V97wpFtuZ4qr65zwHi";  // Put here your Ubidots TOKEN
const char *WIFI_SSID = "Adrian";      // Put here your Wi-Fi SSID
const char *WIFI_PASS = "Gnarnaird";      // Put here your Wi-Fi password
const char *DEVICE_LABEL = "parking";   // Put here your Device label to which data  will be published
const char *VARIABLE_LABEL = "zona1"; // Put here your Variable label to which data  will be published  
const char *VARIABLE_LABELT = "zona2"; // Put here your Variable label to which data  will be published 
const int datapin= 32;
const int datapin2= 35;
int counter = 0;
int counterX = 0;
boolean inn1 = LOW;
boolean inn2 = HIGH;
boolean tomar_dato1_0 = false;
boolean tomar_dato2_0 = false; 
boolean tomar_dato1_1 = false; 
boolean tomar_dato2_1 = false; 
boolean tomar_dato1_2 = false;
boolean tomar_dato2_2 = false; 
boolean tomar_dato1_3 = false;
boolean tomar_dato2_3 = false;   
boolean cambio = false;
int mylugares_1[4] = {0,0,0,0};
int mylugares_2[4] = {0,0,0,0};
int pulsos = 0;
int D_cm = 0; 
int D_cm2 = 0;
Ubidots ubidots(UBIDOTS_TOKEN);

void setup() {
  delay(5000);
   Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(19), boton, RISING);
   pinMode(MOTOR_IN1, OUTPUT);
   pinMode(MOTOR_IN2, OUTPUT);
   digitalWrite(MOTOR_IN1, inn1);
   digitalWrite(MOTOR_IN2, inn2);
  ubidots.connectToWifi(WIFI_SSID, WIFI_PASS);
  ubidots.setup();
  ubidots.reconnect();
}
void loop() {
  if(counterX < 22)
   {
    publicarxd();
    digitalWrite(MOTOR_IN1, inn1);
    digitalWrite(MOTOR_IN2, inn2);
   }
  if (cambio == false)
  {
     if(counterX < 22)
   {
    D_cm = distancia(); 
    D_cm2 = distancia2();
    if(D_cm <= 10)
    {
      mylugares_1[0] = 1;
    }else{
      mylugares_1[0] = 0;
    }
    if(D_cm2 <= 10)
    {
      mylugares_2[0] = 1;
    }else{
      mylugares_2[0] = 0;
    }
   }else if(counterX == 123)
   {
    D_cm = distancia(); 
    D_cm2 = distancia2();
    if(D_cm <= 10)
    {
      mylugares_1[1] = 1;
    }else{
      mylugares_1[1] = 0;
    }
    if(D_cm2 <= 10)
    {
      mylugares_2[1] = 1;
    }else{
      mylugares_2[1] = 0;
    }
   }else if(counterX == 240)
   {
    D_cm = distancia(); 
    D_cm2 = distancia2();
    if(D_cm <= 10)
    {
      mylugares_1[2] = 1;
    }else{
      mylugares_1[2] = 0;
    }
    if(D_cm2 <= 10)
    {
      mylugares_2[2] = 1;
    }else{
      mylugares_2[2] = 0;
    }
   }else if(counterX == 360)
   {
    D_cm = distancia(); 
    D_cm2 = distancia2();
    if(D_cm <= 10)
    {
      mylugares_1[3] = 1;
    }else{
      mylugares_1[3] = 0;
    }
    if(D_cm2 <= 10)
    {
      mylugares_2[3] = 1;
    }else{
      mylugares_2[3] = 0;
     }
   }
  }
}


float distancia()
{
float volts = analogRead( datapin ) * (3.3 / 4096);

int distance_cm = 29.988 * pow( volts , -1.173);
  return (distance_cm);
}

float distancia2()
{
float volts2 = analogRead( datapin2 ) * (3.3 / 4096);

int distance_cm2 = 29.988 * pow( volts2 , -1.173);
  return (distance_cm2);
}

void boton (){
   counterX++;
   if (counterX >= 380)
   {
      digitalWrite(MOTOR_IN1, LOW);
      digitalWrite(MOTOR_IN2, LOW);
      counterX = 0;
      inn1 = !inn1;
      inn2 = !inn2;
     Serial.print("sección 1: ");
     Serial.println(mylugares_1[0]);
     Serial.println(mylugares_1[1]);
     Serial.println(mylugares_1[2]);
     Serial.println(mylugares_1[3]);
     Serial.print("sección 2: ");
     Serial.println(mylugares_2[0]);
     Serial.println(mylugares_2[1]);
     Serial.println(mylugares_2[2]);
     Serial.println(mylugares_2[3]);
      delay(700);
      cambio = !cambio;
   }

 }

 void publicarxd(){
    if (!ubidots.connected())
  {
    ubidots.reconnect();
  }
    float capacity = 0;
    float capacity2 = 0;
    for(int i = 0; i < 4; i = i+1)
    {
      capacity = capacity + mylugares_1[i];
      capacity2 = capacity2 + mylugares_2[i];
    }
    capacity = capacity/4;
    capacity2 = capacity2/4;
    ubidots.add(VARIABLE_LABEL, capacity); // Insert your variable Labels and the value to be sent
    ubidots.add(VARIABLE_LABELT, capacity2); // Insert your variable Labels and the value to be 
    ubidots.publish(DEVICE_LABEL);
  ubidots.loop();
 }
