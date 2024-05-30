#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
int cont=0;
int s1=10,s2=11,s3=12,s4=13;
int v, v1, v2, v3;
LiquidCrystal_I2C lcd(0x27,16,2);  //permite conectat LCD Y I2C

volatile long time;
volatile bool State = false;
long distance;





//,s2,s3,s4;//Variables de los sensores
void setup() {
  
  pinMode(9,OUTPUT);//IN1
  pinMode(3,OUTPUT);//PWM MOTOR 1
  pinMode(4,OUTPUT);//IN2
  pinMode(5,OUTPUT);//PWM MOTOR 2
  pinMode(6,OUTPUT);//IN3
  pinMode(7,OUTPUT);//IN4
  pinMode(s2,INPUT);
  pinMode(s2,INPUT);
  pinMode(s3,INPUT);//Sensor Derecha
  pinMode(s4,INPUT);
  pinMode(2, INPUT);//ECHO-INTERRUPCIÓN
  pinMode(8, OUTPUT);//TRIG
  Serial.begin(9600); 
  attachInterrupt(digitalPinToInterrupt(2), echoISR, CHANGE);
   // Inicializar el LCD
  lcd.init();
  //Encender la luz de fondo.
  lcd.backlight();
  // Escribimos el Mensaje en el LCD.
  lcd.print("AUTO EVASOR");
  
}

void loop() {

  v=digitalRead(s1);//Derecha
  v1=digitalRead(s2);//centro
  v2=digitalRead(s3);//centro
  v3=digitalRead(s4);//izquierda
  if (State) {
    
    distance = time / 58.2; // Convertir a distancia en cm
     
    if (distance<=15) { // Distancia limite para evasión de obstáculos
      cont++;
      lcd.setCursor(0, 1);
      lcd.print("#Obj:");
      lcd.print(cont);
      SPEED_MOTOR();//Función para reducir la velocidad del motor.
      if(distance<=8)
      {
        delay(300);//Pausa para ajuste de giro a 90º DERECHA 
        MOTOR1(200,0,1); //MOTOR IZQUIERD
        MOTOR2(200,0,0); //MOTOR DERECHO
        delay(300);//Pausa para ir adelante
        MOTOR1(200,1,0);  //ADELANTE
        MOTOR2(200,1,0);
        delay(300); //PASUA PARA AJUSTAR 90 A IZQUIERDA
        MOTOR1(200,0,0); //IZQUIERDO
        MOTOR2(200,0,1); //DERECHO
        delay(300);//Pausa para ir adelante
        MOTOR1(200,1,0);  //ADELANTE
        MOTOR2(200,1,0);
        delay(300); //PAUSA PAR APARA AJUSTAR 
        MOTOR1(200,0,0); // IZQUIERADA
        MOTOR2(200,0,1);
        delay(300);
        MOTOR1(200,1,0); //AVABZAR
        MOTOR2(200,1,0);
        delay(300);//Pausa para ajuste de giro a 90º DERECHA 
        MOTOR1(200,0,1); //MOTOR IZQUIERD
        MOTOR2(200,0,0); //MOTOR DERECHO
        delay(300);
        MOTOR1(200,1,0); //AVABZAR
        MOTOR2(200,1,0);

      }
    } 
    else {
     //Avance hacia adelante del motor, cuando no existe obstaculo 89% PWM.
      MOTOR1(180,1,0);
      MOTOR2(180,1,0);
    }
    State = false;
  }
  
  triggerMeasurement();
  delay(100); // Esperar un poco antes de la siguiente medición

   Serial.println(v);
   Serial.println(v1);
   Serial.println(v2);
   Serial.println(v3);
   Serial.println("__");
   
  SEGUIDOR(v,v1,v2,v3);

}


void triggerMeasurement() {
  digitalWrite(8, LOW);
  delayMicroseconds(2);
  digitalWrite(8, HIGH);
  delayMicroseconds(10);
  digitalWrite(8, LOW);
}
/*La función de la interrupción que calcula el tiempo que dura el 
pulso de la onda en ir y volver al obstaculo*/

void echoISR() {
  static unsigned long startTime;
  if (digitalRead(2) == HIGH) {//Cuando el pin ECHO es HIGH calcula tiempo
    startTime = micros();
  } else {
    time = micros() - startTime;
    State = true;
  }
}
//Funciones de Control de Motores
//Los parametros son los terminales del motor y la velocidad

void SEGUIDOR(int st1, int st2, int st3, int st4)
{
  if((st1==0)&&(st4==1))//Los sensores del medio detectan el color negro.
    {
    MOTOR1(150,1,0);
    MOTOR2(150,0,0);
    delay(20);
    }
      else if((st1==1)&&(st4==0))//Los sensores del medio detectan el color negro.
      {
        MOTOR1(150,0,0);
        MOTOR2(150,1,0);
        delay(20);
      }
      else //Los sensores del medio detectan el color negro.
      {
        MOTOR1(150,1,0);
        MOTOR2(150,1,0);
        delay(20);

      }
      
 
}

void MOTOR1 (int PWM,bool IN1,bool IN2)
{
  digitalWrite(9,IN1);
  digitalWrite(4,IN2);
  analogWrite(3,PWM);
}

void MOTOR2 (int PWM,bool IN3,bool IN4)
{
  digitalWrite(6,IN3);
  digitalWrite(7,IN4);
  analogWrite(5,PWM);
}

void SPEED_MOTOR()
{
  int s;
  for (s=120;s>=0;s--)
  {
    MOTOR1(s,0,1);
    MOTOR2(s,0,1);
    delay(16);
  }
}
