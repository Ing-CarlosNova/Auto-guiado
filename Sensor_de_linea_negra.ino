int cont=0;
bool s1,s2,s3,s4;//Variables de los sensores
void setup() {
  pinMode(9,OUTPUT);//IN1
  pinMode(3,OUTPUT);//PWM MOTOR 1
  pinMode(4,OUTPUT);//IN2
  pinMode(5,OUTPUT);//PWM MOTOR 2
  pinMode(6,OUTPUT);//IN3
  pinMode(7,OUTPUT);//IN4
  pinMode(10,INPUT);//Sensor Derecha
  pinMode(11,INPUT);//Sensor Centro Derecha
  pinMode(12,INPUT);//Sensor Centro Izquierda 
  pinMode(13,INPUT);//Sensor Izquierda
  Serial.begin(9600); 
}

void loop() {
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
SEGUIDOR(s1,s2,s3,s4);//Función que controla los motores con los estados.

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
void SEGUIDOR(bool st1,bool st2,bool st3,bool st4)
{

  if((st1==1)&&(st2==1)&&(st3==1)&&(st4==1))//Los sensores detectan negro avanza
    {
      //Robot en Linea Recta
      MOTOR1(180,0,0);
      MOTOR2(180,0,0);
      delay(500);
    }
  
  if((st1==0)&&(st2==1)&&(st3==1)&&(st4==1))//Curva a la izquierda
    {
     //Corrección de Giro a la Derecha
     MOTOR1(180,0,0);
   	 MOTOR2(180,0,1);
     delay(500);
    }
      	/*else
        {
       		if((st1==1)&&(st2==1)&&(st3==1)&&(st4==0))//Curva a la derecha
            {
            //Corrección de Giro a la Izquierdo
        	 MOTOR1(191,0,1);
      	 	 MOTOR2(191,0,0); 
             delay(400);
            }
          	/*else
            {
           		if((st1==1)&&(st2==1)&&(st3==1)&&(st4==1))//Todos los sensores detectan el color negro.
            	{
            	
        	 	MOTOR1(0,0,0);
      	 	 	MOTOR2(0,0,0);
                }
              	else
                {
                MOTOR1(0,0,0);//Variaciones errones que detectan los sensores.
      	 	 	MOTOR2(0,0,0);
                }
            } 
         }*/
      
}

//Espacio para el sensor de fuerza.
