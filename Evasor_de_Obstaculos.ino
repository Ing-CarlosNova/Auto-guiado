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
}

void loop() {
  if (State) {
    
    distance = time / 58.2; // Convertir a distancia en cm
    //Envio de información al monitor serie
    Serial.print("Distancia: ");
    Serial.print(distance);
    Serial.println("cm");
    if (distance<=8) { // Distancia limite para evasión de obstáculos
      MOTOR1(0,0,0);
      MOTOR2(0,0,0);
      delay(700);//Pausa para ajuste de giro
      MOTOR1(125,1,0);
      MOTOR2(125,1,0);
    } 
    else {
      MOTOR1(255,1,0);
      MOTOR2(255,1,0);
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
