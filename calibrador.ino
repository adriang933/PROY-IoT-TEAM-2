#define MOTOR_IN1 4
#define MOTOR_IN2 2     
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
void setup() {
  delay(5000);
   Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(19), boton, RISING);
   pinMode(MOTOR_IN1, OUTPUT);
   pinMode(MOTOR_IN2, OUTPUT);
   digitalWrite(MOTOR_IN1, inn2);
   digitalWrite(MOTOR_IN2, inn1);
}
void loop() {
    delay(1000);
    D_cm = distancia(); 
    D_cm2 = distancia2();
    Serial.print("sección 1: ");
    Serial.println(D_cm);
    Serial.print("sección 2: ");
    Serial.println(D_cm2);
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
   Serial.println(counterX);
   if (counterX >= 380){
      digitalWrite(MOTOR_IN1, LOW);
      digitalWrite(MOTOR_IN2, LOW);
   }
 }
/*Serial.print("sección 1: ");
      Serial.println(D_cm);
      Serial.print("sección 2: ");
      Serial.println(D_cm2);*/
