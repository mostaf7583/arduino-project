// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!
#include <HCSR04.h>

#define trigPin1 A2
#define echoPin1 A5
#define trigPin2 A3
#define echoPin2 A4

#include <AFMotor.h>
int counter = 0;
int zerocount = 0;
AF_DCMotor motor1(1);
int finded = 0;
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);
void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");
  pinMode(trigPin1,OUTPUT);
  pinMode(echoPin1,INPUT);
  pinMode(trigPin2,OUTPUT);
  pinMode(echoPin2,INPUT);

  // turn on motor
  MoveBack();
 
}

void loop() {


 int shit = UFun(trigPin1,echoPin1);
 Serial.println(shit);

   while(UFun(trigPin1,echoPin1)==0){
    return;
    }

if(shit > 10){
  zerocount++;
}

if(zerocount < 70){
  return;
}

if(finded == 1){
   MoveRight();
   delay(2000);
    while(UFun(trigPin2,echoPin2) > 10){
    MoveFront();
    }
    Stop();
   delay(5000);
   return;
}


  Serial.println(UFun(trigPin1,echoPin1));
  int moom = UFun(trigPin1,echoPin1);
  if (moom < 10 && moom > 0) {
    Stop();
    delay(1000);
    finded = 1;
    }
  
  else{
    MoveBack();
  }

  counter++;

}


  void MoveBack(){
  // Turn on motor A
      
  motor1.setSpeed(255); //Define maximum velocity
  motor1.run(BACKWARD); //rotate the motor anti-clockwise
  motor2.setSpeed(255); //Define maximum velocity
  motor2.run(BACKWARD); //rotate the motor anti-clockwise
  motor3.setSpeed(255); //Define maximum velocity
  motor3.run(BACKWARD); //rotate the motor anti-clockwise
  motor4.setSpeed(255); //Define maximum velocity
  motor4.run(BACKWARD); //rotate the motor anti-clockwise
  
  
  }
void MoveLeft(){

  // Turn on motor A

  motor1.setSpeed(255); //Define maximum velocity
  motor1.run(BACKWARD); //rotate the motor anti-clockwise
  motor2.setSpeed(255); //Define maximum velocity
  motor2.run(BACKWARD); //rotate the motor anti-clockwise
  motor3.setSpeed(255); //Define maximum velocity
  motor3.run(FORWARD);  //rotate the motor clockwise
  motor4.setSpeed(255); //Define maximum velocity
  motor4.run(FORWARD);  //rotate the motor clockwise  

  }
void MoveFront(){
      
    // Turn on motor A

motor1.setSpeed(255); //Define maximum velocity
  motor1.run(FORWARD);  //rotate the motor clockwise
  motor2.setSpeed(255); //Define maximum velocity
  motor2.run(FORWARD);  //rotate the motor clockwise
  motor3.setSpeed(255); //Define maximum velocity
  motor3.run(FORWARD); //rotate the motor anti-clockwise
  motor4.setSpeed(255); //Define maximum velocity
  motor4.run(FORWARD); //rotate the motor anti-clockwise
}

     
void Stop(){
  // Now turn off motors
 
  motor1.setSpeed(0);  //Define minimum velocity
  motor1.run(RELEASE); //stop the motor when release the button
  motor2.setSpeed(0);  //Define minimum velocity
  motor2.run(RELEASE); //rotate the motor clockwise
  motor3.setSpeed(0);  //Define minimum velocity
  motor3.run(RELEASE); //stop the motor when release the button
  motor4.setSpeed(0);  //Define minimum velocity
  motor4.run(RELEASE); //stop the motor when release the button
  
  }
void MoveForward() {
    // Turn on motor A

  motor1.setSpeed(255); //Define maximum velocity
  motor1.run(FORWARD);  //rotate the motor clockwise
  motor2.setSpeed(255); //Define maximum velocity
  motor2.run(FORWARD);  //rotate the motor clockwise
  motor3.setSpeed(255); //Define maximum velocity
  motor3.run(FORWARD);  //rotate the motor clockwise
  motor4.setSpeed(255); //Define maximum velocity
  motor4.run(FORWARD);  //rotate the motor clockwise


}

void MoveRight(){
      
    // Turn on motor A

motor1.setSpeed(255); //Define maximum velocity
  motor1.run(FORWARD);  //rotate the motor clockwise
  motor2.setSpeed(200); //Define maximum velocity
  motor2.run(BACKWARD);  //rotate the motor clockwise
  motor3.setSpeed(200); //Define maximum velocity
  motor3.run(BACKWARD); //rotate the motor anti-clockwise
  motor4.setSpeed(255); //Define maximum velocity
  motor4.run(FORWARD); //rotate the motor anti-clockwise
}

int UFun(int triger , int echo){//ultrasonic reading 
   long duration ;
   int distance;
        digitalWrite(triger,LOW);
        delayMicroseconds(2);
        digitalWrite(triger, HIGH);
        delayMicroseconds(10);
        digitalWrite(triger,LOW);
    
        duration = pulseIn(echo,HIGH);
        distance = duration/2 /29.1 ; // 331.5 m/s ===> 0 C.....331.5 +0.6*temp....343.5*100/1000000=.03435cm/us
  return distance; 
  
  }
