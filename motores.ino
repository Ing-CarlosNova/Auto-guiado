void MOTOR1 (int PWM,bool IN1,bool IN2);
void MOTOR2 (int PWM,bool IN3,bool IN4);



void setup() {
pinMode(2,OUTPUT);//IN1
pinMode(3,OUTPUT);//PWM MOTOR 1
pinMode(4,OUTPUT);//IN2
pinMode(5,OUTPUT);//PWM MOTOR 2
pinMode(6,OUTPUT);//IN3
pinMode(7,OUTPUT);//IN4

}

void loop() {
MOTOR1(255,1,0);
MOTOR2(255,1,0);
delay(500);
MOTOR1(255,0,1);
MOTOR2(255,0,1);
delay(500);
 

}
void MOTOR1 (int PWM,bool IN1,bool IN2)
{
digitalWrite(2,IN1);
digitalWrite(4,IN2);
analogWrite(3,PWM);
}

void MOTOR2 (int PWM,bool IN3,bool IN4)
{
digitalWrite(6,IN3);
digitalWrite(7,IN4);
analogWrite(5,PWM);
}

