//www.elegoo.com
/* BLUETOOTH CAR
  This combines the bluetooth blink program with basic car movement controls.

  The elegoo bt16 module does not use standard bluetooth protocol. It uses
  LE protocol. 
  Follow this tutorial to get it working.
  https://www.youtube.com/watch?v=lUUg4wlq4wg
*/
#include <Servo.h>  //servo library
Servo myservo;      // create servo object to control servo

int Echo = A4;  
int Trig = A5; 

#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11
#define LED 13    //Define 13 pin for LED
#define carSpeed 150 // speed can be 0-255
bool state = LOW; //The initial state of the function is defined as a low level
char getstr;      //Defines a function that receives the Bluetooth character
int rightDistance = 0, leftDistance = 0, middleDistance = 0;
int angle = 90;
int delta = 10;

void setup() {
   myservo.attach(3,700,2400);  // attach servo on pin 3 to servo object
  Serial.begin(9600);     
  pinMode(Echo, INPUT);    
  pinMode(Trig, OUTPUT);  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(LED, OUTPUT);
  stop();
  Serial.println("Car Speed: " + carSpeed);
}

void loop() {
  if(Serial.available())
  {
    //The Bluetooth serial port to receive the data in the function
    getstr = Serial.read();
    
    if(getstr == 'a'){
      forward(200,500);
      Serial.print(getstr);
    }
    else if(getstr == 's')
      stop(500);
  }
}// END LOOP

// FUNCTION DEFINITIONS
//Control LED sub function
void stateChange() {
  state = !state; 
  digitalWrite(LED, state);  
}

void scan(){
    myservo.write(angle);  //set servo position according to scaled value
    middleDistance = Distance_test();
    Serial.println(middleDistance);
    delay(50); 
    angle+=delta;
    if( angle > 170 || angle < 10 )
      delta = -delta; 
}

void forward(){ 
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Forward");
}
void forward(int speed){ // 0-255 but 100 is usually minimum
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Forward");
}
void forward(int speed, int delayTime){ 
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(delayTime);
  Serial.println("Forward");
}

void back() {
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Back");
}
void back(int speed) {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Back");
}
void back(int speed, int delayTime) {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(delayTime);
  Serial.println("Back");
}

void left() {
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH); 
  Serial.println("Left");
}
void left(int speed) {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH); 
  Serial.println("Left");
}
void left(int speed, int delayTime) {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH); 
  delay(delayTime);
  Serial.println("Left");
}

void right() {
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Right");
}
void right(int speed) {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Right");
}
void right(int speed, int delayTime) {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(delayTime);
  Serial.println("Right");
}

void stop() {
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  Serial.println("Stop!");
} 
void stop(int delayTime) {
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  delay(delayTime);
  Serial.println("Stop!");
} 
//Ultrasonic distance measurement Sub function
int Distance_test() { // determine distance in centimeters
  digitalWrite(Trig, LOW);   
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  
  delayMicroseconds(20);
  digitalWrite(Trig, LOW);   
  float time = pulseIn(Echo, HIGH); // microseconds 
  float distance = time / 58; // centimeters
  Serial.println( (int) distance ); 
  return (int) distance;
}  
