#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//Crear el objeto lcd  dirección  0x3F y 16 columnas x 2 filas
LiquidCrystal_I2C lcd(0x27,16,2);  //

int cont=0;
volatile long time;
volatile bool State = false;
long distance;
void setup() {
  pinMode(9,OUTPUT);//IN1
  pinMode(3,OUTPUT);//PWM MOTOR 1
  pinMode(4,OUTPUT);//IN2
  pinMode(5,OUTPUT);//PWM MOTOR 2
  pinMode(6,OUTPUT);//IN3
  pinMode(7,OUTPUT);//IN4
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
        delay(1000);//Pausa para ajuste de giro a 90º DERECHA 
        MOTOR1(200,0,1); //MOTOR IZQUIERD
        MOTOR2(200,0,0); //MOTOR DERECHO
        delay(1000);//Pausa para ir adelante
        MOTOR1(200,1,0);  //ADELANTE
        MOTOR2(200,1,0);
        delay(1000); //PASUA PARA AJUSTAR 90 A IZQUIERDA
        MOTOR1(200,0,0); //IZQUIERDO
        MOTOR2(200,0,1); //DERECHO
        delay(1000);//Pausa para ir adelante
        MOTOR1(200,1,0);  //ADELANTE
        MOTOR2(200,1,0);
        delay(1000); //PAUSA PAR APARA AJUSTAR 
        MOTOR1(200,0,0); // IZQUIERADA
        MOTOR2(200,0,1);
        delay(1000);
        MOTOR1(200,1,0); //AVABZAR
        MOTOR2(200,1,0);
        delay(1000);//Pausa para ajuste de giro a 90º DERECHA 
        MOTOR1(200,0,1); //MOTOR IZQUIERD
        MOTOR2(200,0,0); //MOTOR DERECHO
        delay(1000);
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
