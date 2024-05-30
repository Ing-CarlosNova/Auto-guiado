int cont=0;
int s1=10,s2=11,s3=12,s4=13;
int v, v1, v2, v3;

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

  Serial.begin(9600); 
}

void loop() {
  v=digitalRead(s1);//Derecha
  v1=digitalRead(s2);//Derecha
  v2=digitalRead(s3);//Derecha
  v3=digitalRead(s4);//Derecha

   Serial.println(v);
   Serial.println(v1);
   Serial.println(v2);
   Serial.println(v3);
   Serial.println("__");

  SEGUIDOR(v,v1,v2,v3);

}

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

