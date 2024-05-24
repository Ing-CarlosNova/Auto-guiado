#include <Wire.h>
#include <LiquidCrystal_I2C.h>


//Crear el objeto lcd  dirección  0x3F y 16 columnas x 2 filas
LiquidCrystal_I2C lcd(0x20,16,2);  //Configuración de la LCD con I2C
void SEGUIDOR();
int cont=0;
volatile long time,time2;//
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
   // Inicializar el LCD
  lcd.init();
  //Encender la luz de fondo.
  lcd.backlight();
  // Escribimos el Mensaje en el LCD.
  lcd.print("Hola Mundo");
}

void loop() {
  if (State) {
    
    distance = time / 58.2; // Convertir a distancia en cm
    //Envio de información al monitor serie
    Serial.print("Distancia: ");
    Serial.print(distance);
    Serial.println("cm");
    if (distance<=15) { // Distancia limite para evasión de obstáculos
      cont++;
      lcd.setCursor(0, 1);
      lcd.print("#Obj:");
      lcd.print(cont);
      SPEED_MOTOR();//Función para reducir la velocidad del motor.
      if(distance<=8)
      {
      delay(2000);//Pausa para ajuste de giro a 90º
      MOTOR1(191,0,0);
      MOTOR2(191,1,0);
      delay(700);//Pausa para ir adelante
      MOTOR1(226,0,1);
      MOTOR2(226,0,1);
      delay(700);
      MOTOR1(191,0,1);
      MOTOR2(191,0,0);
      }
    peso=SENSOR_MF01();//Calculo de peso con la ecuación m=f/a y a=9.8 m/s^2
    Serial.print("Peso=");
  	Serial.println(peso);
    } 
    else {
     //Avance hacia adelante del motor, cuando no existe obstaculo 89% PWM.
      //MOTOR1(120,1,0);
      //MOTOR2(120,1,0);
      SEGUIDOR();
      peso=SENSOR_MF01();//Calculo de peso con la ecuación m=f/a y a=9.8 m/s^2
      Serial.print("Peso=");
  	  Serial.println(peso);
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
//
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
void SEGUIDOR()
{

s1=digitalRead(10);//Derecha
s2=digitalRead(11);//Centro Derecha
s3=digitalRead(12);//Centro Izquierda
s4=digitalRead(13);//Izquierda
if((s1==0)&&(s2==1)&&(s3==1)&&(s4==0))
{
 start_time2=millis();
  //Medición de peso
 delay(7000);
 //Robot en Linea Recta
 MOTOR1(120,1,0);
 MOTOR2(120,1,0);
}
    else
    {
     	if((s1==0)&&(s2==1)&&(s3==0)&&(s4==0))
        {
         //Corrección de Giro a la Derecha
         MOTOR1(191,0,0);
      	 MOTOR2(191,1,0);
         delay(400);
        }
      	else
        {
       		if((s1==0)&&(s2==0)&&(s3==1)&&(s4==0))
            {
            //Corrección de Giro a la Derecha
        	 MOTOR1(191,1,0);
      	 	 MOTOR2(191,0,0); 
             delay(400);
            }
          	else
            {
           		if((s1==0)&&(s2==0)&&(s3==0)&&(s4==0))
            	{
            	//Avanzar cuando los sensores esten todos
                // en blanco
        	 	SPEED_MOTOR();
                }
              	else
                {
                MOTOR1(0,0,0);
      	 	 	MOTOR2(0,0,0);
                time2=millis()-start_time2;
                }
            } 
         }
      }
}

//Espacio para el sensor de fuerza.
