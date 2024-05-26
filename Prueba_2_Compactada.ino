#include <LiquidCrystal_I2C.h>
#include <Wire.h>

//Crear el objeto lcd  dirección  0x3F y 16 columnas x 2 filas
LiquidCrystal_I2C lcd(0x20,16,2);  //
void SEGUIDOR();
int cont,fuerza;
volatile long time,time2;
volatile bool State = false;
long distance;
bool s1,s2,s3,s4;//Variables de los sensores
unsigned long start_time2;
float peso;
void setup() {
  pinMode(9,OUTPUT);//IN1
  pinMode(3,OUTPUT);//PWM MOTOR 1
  pinMode(4,OUTPUT);//IN2
  pinMode(5,OUTPUT);//PWM MOTOR 2
  pinMode(6,OUTPUT);//IN3
  pinMode(7,OUTPUT);//IN4
  pinMode(2, INPUT);//ECHO-INTERRUPCIÓN
  pinMode(8, OUTPUT);//TRIG
  pinMode(10,INPUT);//Sensor Derecha
  pinMode(11,INPUT);//Sensor Centro Derecha
  pinMode(12,INPUT);//Sensor Centro Izquierda 
  pinMode(13,INPUT);//Sensor Izquierda
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2), echoISR, CHANGE);
  lcd.init();// Inicializar el LCD
  lcd.backlight();//Encender la luz de fondo.
  lcd.setCursor(0,0);
  lcd.print("Proyecto ");// Escribimos el Mensaje en el LCD.
  lcd.setCursor(0,1);
  lcd.print("S Embebidos");
  delay(200);
  lcd.clear();
}

void loop() {
  if (State) {
    
    distance = time / 58.2; // Convertir a distancia en cm
    //Envio de información al monitor serie de la distancia
    Serial.print("Distancia: ");
    Serial.print(distance);
    Serial.println("cm");
    if (distance<=15) { // Distancia limite para evasión de obstáculos
      cont++;//Conteo de obstaculos.
      fuerza=SENSOR_MF01(0);//Función de lectura de sensor de peso.
      mensage(cont,fuerza);//Función para mostras el conteo de objetos y la fuerza.
      SPEED_MOTOR();//Función para reducir la velocidad del motor.
      if(distance<=8)
      {
      delay(2000);//Pausa para ajuste de giro a 90º
      MOTORES (191,0,0,191,1,0);
      delay(700);//Pausa para ir adelante
      MOTORES (226,0,1,226,0,1);
      delay(700);
      MOTORES (191,0,1,191,0,0);
      }
    
  	Serial.println(peso);
    } 
    else {
      s1=digitalRead(10);//Derecha
	  s2=digitalRead(11);//Centro Derecha
	  s3=digitalRead(12);//Centro Izquierda
	  s4=digitalRead(13);//Izquierda
      //Impresión de Estados de los Sensores 
		Serial.println(s1);
		Serial.println(s2);
		Serial.println(s3);
		Serial.println(s4);
		Serial.println("____");
        SEGUIDOR(s1,s2,s3,s4);//Función que controla los motores con los estados.      peso=SENSOR_MF01();//Calculo de peso con la ecuación m=f/a y a=9.8 m/s^2
		fuerza=SENSOR_MF01(0);//Función de lectura de sensor de peso.
        mensage(cont,fuerza);//Función para mostras el conteo de objetos y la fuerza.
    }
    State = false;
  }
  
  triggerMeasurement();
  delay(100); // Esperar un poco antes de la siguiente medición
}
//Genera el pulso que desencadena la medida del sensor.
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
void MOTORES (int PWM_M1,bool IN1,bool IN2,int PWM_M2,bool IN3,bool IN4)
{
digitalWrite(9,IN1);
digitalWrite(4,IN2);
analogWrite(3,PWM_M1);
digitalWrite(6,IN3);
digitalWrite(7,IN4);
analogWrite(5,PWM_M2);
}

//Función de reducción de velocidad de motores 1 y 2 
void SPEED_MOTOR()
{
 int s;
 for (s=120;s>=0;s--)
 {
 MOTORES(s,0,1,s,0,1);
 delay(16);
 }
}

/*Función de control de seguidor de linea negra con 4 sensores*/
void SEGUIDOR(bool st1,bool st2,bool st3,bool st4)
{

if((st1==0)&&(st2==1)&&(st3==1)&&(st4==0))//Los sensores del medio detectan el color negro.
{
 delay(400);
 //Robot en Linea Recta
 MOTORES (120,1,0,120,1,0);
}
    else
    {
     	if((st1==0)&&(st2==1)&&(st3==0)&&(st4==0))//Curva a la derecha-Sensor Central Derecho Detecta Unicamente
        {
         //Corrección de Giro a la Derecha
         MOTORES (191,0,0,191,1,0);
         delay(400);
        }
      	else
        {
       		if((st1==0)&&(st2==0)&&(st3==1)&&(st4==0))//Curva a la izquierda-Sensor Central Izquierdo Detecta Unicamente
            {
            //Corrección de Giro a la Izquierdo        	
             MOTORES (191,1,0,191,0,0);
             delay(400);
            }
          	else
            {
           		if((st1==1)&&(st2==1)&&(st3==1)&&(st4==1))//Todos los sensores detectan el color negro.
            	{
                MOTORES(0,0,0,0,0,0);
                }
              	else
                {
                //Variaciones errones que detectan los sensores.
                MOTORES(0,0,0,0,0,0);
                }
            } 
         }
      }
}

//Espacio para el sensor de fuerza.
int SENSOR_MF01(int pin)
{
  int data;
  data=analogRead(pin);
  return data;
}

void mensage (int ct, int f)
{
lcd.setCursor(0,1);
lcd.print("#Obj:");
lcd.print(ct);
lcd.setCursor(0,0);
lcd.print("Peso=");
lcd.print(f);
lcd.print("g"); 
}









  
