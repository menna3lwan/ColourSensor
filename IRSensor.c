#include <Servo.h> 

#define irpin 11
#define ledWhite 3
#define ledBlack 2
#define servo_pin 6 
#define echo 12
#define trig 13

Servo servo_motor; 


void setup(){
  
  pinMode(ledWhite,OUTPUT);
  pinMode(irpin,INPUT);
  pinMode(ledBlack,OUTPUT);
  
  pinMode(trig,OUTPUT);  //transmit infra_red
  pinMode(echo,INPUT);  // receive infra_red to calculate distance
  
  servo_motor.attach(servo_pin);
  
  //Serial.begin(9600);
  
 
}

void loop(){
 
   int ir_read=digitalRead(irpin);
    
  ultrasonic(ir_read);
  
}


void ultrasonic(int ir_read){
  
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  
  digitalWrite(trig,LOW);
  
  int duration=pulseIn(echo,HIGH);
  
  int distance=duration*0.0343/2;
    
    //Serial.println(distance);
  
  if(distance<=20){
    servo(ir_read);
  }
  
  else{
    
   // initial angle = 90
  servo_motor.write(90);
  delay(100);
  }
  
  
}

//ir_Sensor reading

int ir_sensor(int ir_read){
 
  int flag=0;

  if(ir_read==HIGH){
    
    digitalWrite(ledWhite,HIGH);
    digitalWrite(ledBlack,LOW);
    flag=1;
  }
  else{
    
     digitalWrite(ledBlack,HIGH);
     digitalWrite(ledWhite,LOW);
     flag=0;
  }
  
  return flag;
  
}

//the direction of the Servo depend on color object

void servo(int ir_read){

    //if ir_sensor detect black object 
   //left
  if( ir_sensor(ir_read)==0){
    servo_motor.write(180);
    delay(500);
    
  }
  
    // if ir_sensor detect white object
   // right
 else if( ir_sensor(ir_read)==1){
   servo_motor.write(0);
   delay(500);
   
  


   }
  
}




