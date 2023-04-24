#define MOTOR_IN1 4
#define MOTOR_IN2 2     
const int datapin= 35;
const int datapin2= 34;
unsigned long tiempo_1 = 0;
unsigned long tiempo_2 = 0;
unsigned long tiempo_3 = 0;
int counter = 0;
boolean inn1 = LOW;
boolean inn2 = HIGH;
boolean bandera = false;
boolean tomar_dato = false; 
int mylugares_1[5] = {0,0,0,0,0};
int mylugares_2[5] = {0,0,0,0,0};
int pulsos = 0;
void setup() {
  delay(5000);
   Serial.begin(9600);
   pinMode(MOTOR_IN1, OUTPUT);
   pinMode(MOTOR_IN2, OUTPUT);
   digitalWrite(MOTOR_IN1, inn1);
   digitalWrite(MOTOR_IN2, inn2);
   tiempo_1 = micros();

}
void loop() {
   tiempo_2 = micros();
   tiempo_3 = tiempo_2 - tiempo_1;

  if( 500000 <= tiempo_3){
    tomar_dato = true;
  }
  if(true == tomar_dato){
    tiempo_1 = tiempo_2;
    tomar_dato = false;
    int D_cm = distancia(); 
    int D_cm2 = distancia2(); 
    if( D_cm < 15){
      mylugares_1[counter] = 1;
      
    }else{
      mylugares_1[counter] = 0;
    }
     if( D_cm2 < 15){
      mylugares_2[counter] = 1;
    }else{
      mylugares_2[counter] = 0;
    }

  Serial.print("espacio ");
  Serial.println(counter);
  Serial.print("sección 1: ");
  Serial.println(mylugares_1[counter]);
  Serial.print("sección 2: ");
  Serial.println(mylugares_2[counter]);
  if (bandera == false){
     counter++;
  }
  if (bandera == true){
    counter--;
  }
    if((counter == 4) && (bandera == false)){
      bandera = !bandera;
      inn1 = !inn1;
      inn2 = !inn2;
      digitalWrite(MOTOR_IN1, LOW);
      digitalWrite(MOTOR_IN2, LOW);
      delay(500);
      digitalWrite(MOTOR_IN1, inn1);
      digitalWrite(MOTOR_IN2, inn2);
    }else if ((counter == 0) && (bandera == true)){
      bandera = !bandera;
      inn1 = !inn1;
      inn2 = !inn2;
      digitalWrite(MOTOR_IN1, LOW);
      digitalWrite(MOTOR_IN2, LOW);
      delay(500);
      digitalWrite(MOTOR_IN1, inn1);
      digitalWrite(MOTOR_IN2, inn2);
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
