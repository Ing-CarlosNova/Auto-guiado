#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
int cont=0;
int s1=10,s2=11,s3=12,s4=13;
int v, v1, v2, v3;
LiquidCrystal_I2C lcd(0x27,16,2);  //permite conectat LCD Y I2C

volatile long time;
volatile bool State = false;
long distance;
int cont_lineas=0;
unsigned long tiempo1,tiempo2,tiempoSegundos;
//fuerza 
int FSR_PIN = A0;
float VCC = 5.0; // Voltaje de alimentación del Arduino
float R_DIV = 10000.0; // Valor de la resistencia de 10kΩ en ohmios
float weight;

const int numReadings = 10;
float readings[numReadings]; // Array to store readings
int readIndex = 0; // Index of the current reading
float total = 0; // Running total
float average = 0; // Average of the readings


//,s2,s3,s4;//Variables de los sensores
void setup() {
  
  pinMode(9,OUTPUT);//IN1
  pinMode(3,OUTPUT);//PWM MOTOR 1
  pinMode(4,OUTPUT);//IN2
  pinMode(5,OUTPUT);//PWM MOTOR 2
  pinMode(6,OUTPUT);//IN3
  pinMode(7,OUTPUT);//IN4
  pinMode(s1,INPUT); //sensor derecha
  pinMode(s2,INPUT); //sensor centro derecho
  pinMode(s3,INPUT);//sensor centro izquierdo
  pinMode(s4,INPUT); // izquierdo
  pinMode(2, INPUT);//ECHO-INTERRUPCIÓN
  pinMode(8, OUTPUT);//TRIG
  Serial.begin(9600); 
  attachInterrupt(digitalPinToInterrupt(2), echoISR, CHANGE);
   // Inicializar el LCD
  lcd.init();
  //Encender la luz de fondo.
  lcd.backlight();

  for (int i = 0; i < numReadings; i++) {
    readings[i] = 0;
  }
  
}

void loop() {
  
  if (State) {
    
    distance = time / 58.2; // Convertir a distancia en cm
    int fsrADC = analogRead(FSR_PIN);
    MF01(fsrADC);
     lcd_mensage(tiempoSegundos,cont,weight);
    if (distance<=15) { // Distancia limite para evasión de obstáculos
     
      lcd_mensage(tiempoSegundos,cont,weight);
      SPEED_MOTOR();//Función para reducir la velocidad del motor.
      if(distance<=8)
      {
         cont++;
        delay(1000);//Pausa para ajuste de giro a 90º DERECHA 
        MOTOR1(180,0,1); //MOTOR IZQUIERD
        MOTOR2(180,0,0); //MOTOR DERECHO
        delay(500);//Pausa para ir adelante
        MOTOR1(180,1,0);  //ADELANTE
        MOTOR2(180,1,0);
        delay(1000); //PASUA PARA AJUSTAR 90 A IZQUIERDA
        MOTOR1(180,0,0); //IZQUIERDO
        MOTOR2(180,0,1); //DERECHO
        delay(500);//Pausa para ir adelante
        MOTOR1(180,1,0);  //ADELANTE
        MOTOR2(180,1,0);
        delay(500); //PAUSA PAR APARA AJUSTAR 
        MOTOR1(180,0,0); // IZQUIERADA
        MOTOR2(180,0,1);
        delay(500);
        MOTOR1(180,1,0); //AVABZAR
        MOTOR2(180,1,0);
        delay(1000);//Pausa para ajuste de giro a 90º DERECHA 
        MOTOR1(180,0,1); //MOTOR IZQUIERD
        MOTOR2(180,0,0); //MOTOR DERECHO
        delay(500);
        MOTOR1(180,1,0); //AVABZAR
        MOTOR2(180,1,0);

      }
    } 
    else {
     //Avance hacia adelante del motor, cuando no existe obstaculo 89% PWM.
      MOTOR1(180,1,0);
      MOTOR2(180,1,0);
      SEGUIDOR(v,v1,v2,v3);
    }
    State = false;
  }
  
  triggerMeasurement();
  delay(100); // Esperar un poco antes de la siguiente medición
 
  v=digitalRead(s1);//Derecha
  v1=digitalRead(s2);//centro
  v2=digitalRead(s3);//centro
  v3=digitalRead(s4);//izquierda

   Serial.println(v);
   Serial.println(v1);
   Serial.println(v2);
   Serial.println(v3);
   Serial.println("__");
   
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
  if(st4==1)//Los sensores del medio detectan el color negro.
    {
    MOTOR1(150,0,0);
    MOTOR2(0,0,0);
    delay(20);
    }
      else if(st1==1)//Los sensores del medio detectan el color negro.
      {
        MOTOR1(0,0,0);
        MOTOR2(150,0,0);
        delay(20);
      }
      else //Los sensores del medio detectan el color negro.
      {
        MOTOR1(150,1,0);
        MOTOR2(150,1,0);
        delay(20);

      }
  if ((st2==1)&&(st3==1))
  {
    
    tiempo2 = millis();
      if(tiempo2 > (tiempo1+1000))
      {  //Si ha pasado 1 segundo ejecuta el IF
        tiempo1 = millis(); //Actualiza el tiempo actual
        tiempoSegundos = tiempo1/1000;
        lcd_mensage(tiempoSegundos,cont,weight);
      }
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

void lcd_mensage(long t,int obj,float p)
{
lcd.setCursor(0,0);
lcd.print("#Obj:");
lcd.print(obj);
lcd.setCursor(0,1);
lcd.print("Time:");
lcd.print(t);
lcd.print("s"); 
lcd.print("P=");
lcd.print(p);
lcd.print("Kg");
}

void MF01 (float pc)
{
   
 
  total = total - readings[readIndex];
  readings[readIndex] = analogRead(pc);
  total = total + readings[readIndex];
  readIndex = readIndex + 1;
  if (readIndex >= numReadings) {
    readIndex = 0;
  }
  average = total / numReadings;
 
  float fsrV =  average * (VCC / 1023.0);
  float fsrR = R_DIV * (VCC / fsrV - 1.0);
  float force = 0; 

  if (fsrR <= 600) {
    force = (pc - 600) / 6000; // Esto depende del modelo y debe ajustarse
  } else {
    force = (pc - 600) / 250; // Esto depende del modelo y debe ajustarse
  }

  // Convertir la fuerza de Newtons a kilogramos (1 Newton = 0.10197 kg)
  weight = force * 0.10197;
    // Imprimir los resultados
  /*Serial.print("ADC Value: ");
  Serial.print(fsrADC);
  Serial.print("\tVoltage: ");
  Serial.print(fsrV);
  Serial.print(" V\tResistance: ");
  Serial.print(fsrR);
  Serial.print(" ohms\tForce: ");
  Serial.print(force);
  Serial.print(" N\tWeight: ");*/
  Serial.print(weight);
  Serial.println(" kg");

  delay(500);
}
