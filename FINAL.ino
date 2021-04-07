#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

//define logic control output pin
#define trigPin1 13
#define echoPin1 12

#define trigPin2 A3
#define echoPin2 A2

#define trigPin3 7
#define echoPin3 6

#define trigPin4 9
#define echoPin4 8

#define trigPin5 A1
#define echoPin5 A0

#define trigPin6 11
#define echoPin6 10

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor  = AFMS.getMotor(1);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);
Adafruit_DCMotor *myMotor3 = AFMS.getMotor(3);
Adafruit_DCMotor *myMotor4 = AFMS.getMotor(4);

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  
  // Configure the pin modes for each drive motor
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  
  pinMode(trigPin4, OUTPUT);
  pinMode(echoPin4, INPUT);

  pinMode(trigPin5, OUTPUT);
  pinMode(echoPin5, INPUT);

  pinMode(trigPin6, OUTPUT);
  pinMode(echoPin6, INPUT);
  
  AFMS.begin();  // create with the default frequency 1.6KHz

  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor->setSpeed(100);
  myMotor->run(BACKWARD);

  myMotor2->setSpeed(100);
  myMotor2->run(FORWARD);
  
  myMotor3->setSpeed(100);
  myMotor3->run(FORWARD);

  myMotor4->setSpeed(100);
  myMotor4->run(BACKWARD);
}

void loop() {
  long duration1, distance1;
  long duration2, distance2;
  long duration3, distance3;
  long duration4, distance4;
  long duration5, distance5;
  long duration6, distance6;
  long a, b, c, d, e;
  
  digitalWrite(trigPin1, LOW); // Sets the trigPin1 on LOW state for 2 micro seconds
  delayMicroseconds(2); 
  digitalWrite(trigPin1, HIGH); // Sets the trigPin1 on HIGH state for 10 micro seconds
  delayMicroseconds(10); 
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH); // Reads the echoPin1, returns the sound wave travel time in microseconds

  digitalWrite(trigPin2, LOW); // Sets the trigPin2 on LOW state for 2 micro seconds
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH); // Sets the trigPin2 on HIGH state for 10 micro seconds
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH); // Reads the echoPin2, returns the sound wave travel time in microseconds
  
  digitalWrite(trigPin3, LOW); // Sets the trigPin3 on LOW state for 2 micro seconds
  delayMicroseconds(2);
  digitalWrite(trigPin3, HIGH); // Sets the trigPin3 on HIGH state for 10 micro seconds
  delayMicroseconds(10); 
  digitalWrite(trigPin3, LOW);
  duration3 = pulseIn(echoPin3, HIGH); // Reads the echoPin3, returns the sound wave travel time in microseconds
  
  digitalWrite(trigPin4, LOW);  // Sets the trigPin4 on LOW state for 2 micro seconds
  delayMicroseconds(2); 
  digitalWrite(trigPin4, HIGH); // Sets the trigPin4 on HIGH state for 10 micro seconds
  delayMicroseconds(10);
  digitalWrite(trigPin4, LOW);
  duration4 = pulseIn(echoPin4, HIGH); // Reads the echoPin4, returns the sound wave travel time in microseconds

  digitalWrite(trigPin5, LOW); // Sets the trigPin5 on LOW state for 2 micro seconds
  delayMicroseconds(2);
  digitalWrite(trigPin5, HIGH); // Sets the trigPin5 on HIGH state for 10 micro seconds
  delayMicroseconds(10);
  digitalWrite(trigPin5, LOW);
  duration5 = pulseIn(echoPin5, HIGH); // Sets the trigPin5 on HIGH state for 10 micro seconds

  digitalWrite(trigPin6, LOW); // Sets the trigPin6 on LOW state for 2 micro seconds
  delayMicroseconds(2);
  digitalWrite(trigPin6, HIGH); // Sets the trigPin6 on HIGH state for 10 micro seconds
  delayMicroseconds(10);
  digitalWrite(trigPin6, LOW);
  duration6 = pulseIn(echoPin6, HIGH); // Sets the trigPin6 on HIGH state for 10 micro seconds
  
  // Calculating the distance
  distance1 = (duration1 /2) / 29.1;
  distance2 = (duration2 /2) / 29.1;
  distance3 = (duration3 /2) / 29.1;
  distance4 = (duration4 /2) / 29.1;
  distance5 = (duration5 /2) / 29.1;
  distance6 = (duration6 /2) / 29.1;
  
  // Prints the distance on the Serial Monitor
  Serial.print(distance1);
  Serial.println(" cm");
  Serial.print(distance2);
  Serial.println(" cm");
  Serial.print(distance3);
  Serial.println(" cm");
  Serial.print(distance4);
  Serial.println(" cm");
  Serial.print(distance5);
  Serial.println(" cm");
  Serial.print(distance6);
  Serial.println(" cm");
  Serial.println("\n");
  
  a = stop0(distance1, distance2, distance5, distance6);
  b = move1(distance1, distance2, distance5, distance6);
  c = move2(distance1, distance2, distance5, distance6);
  d = turn1(distance1, distance2, distance3, distance4, distance5);
  e = turn2(distance1, distance2, distance3, distance4, distance5);
}

long stop0 (long dis1, long dis2, long dis5, long dis6) //define stop function
{
  if (dis1 <= 8 && dis2 <= 8 && dis5 <=8 && dis6 <= 8) 
   {
     myMotor ->run(RELEASE);
     myMotor2->run(RELEASE);
     myMotor3->run(RELEASE);
     myMotor4->run(RELEASE);
     Serial.println("stop0");
   } 
}
long move1 (long dis1, long dis2, long dis5, long dis6) //define forward function
{
  if (dis1 < 8 && dis2 > 4 && dis5 > 4 && dis6 < 8) {
    Serial.println("move1");
    myMotor ->run(FORWARD);
    myMotor2->run(BACKWARD);
    myMotor3->run(BACKWARD);
    myMotor4->run(FORWARD);
    myMotor ->setSpeed(100);
    myMotor2->setSpeed(100);
    myMotor3->setSpeed(100);
    myMotor4->setSpeed(100);
    delay(100);
 }
}

long move2 (long dis1, long dis2, long dis5, long dis6) //define backward function
{
  if (dis2 < 4 && dis1 > 8 && dis5 < 4 && dis6 > 8) 
  {
    Serial.println("move2");
    myMotor ->run(BACKWARD);
    myMotor2->run(FORWARD);
    myMotor3->run(FORWARD);
    myMotor4->run(BACKWARD);
    myMotor ->setSpeed(100);
    myMotor2->setSpeed(100);
    myMotor3->setSpeed(100);
    myMotor4->setSpeed(100);
    delay(100);
 }
}

long turn1 (long dis1, long dis2, long dis3, long dis4, long dis5) //define right turn function
{
  long dur1, dur2, dur3, dur4, dur5, dur6;
  while (dis2 > 7 && dis3 < 9 && dis4 > 2 && dis5 > 9){
    Serial.println("turn1");
    myMotor ->run(FORWARD);
    myMotor2->run(BACKWARD);
    myMotor3->run(BACKWARD);
    myMotor4->run(FORWARD);
    myMotor ->setSpeed(200);
    myMotor2->setSpeed(200);
    myMotor3->setSpeed(20);
    myMotor4->setSpeed(20);
    
    digitalWrite(trigPin1, LOW); // Sets the trigPin1 on LOW state for 2 micro seconds
    delayMicroseconds(2); 
    digitalWrite(trigPin1, HIGH); // Sets the trigPin1 on HIGH state for 10 micro seconds
    delayMicroseconds(10); 
    digitalWrite(trigPin1, LOW);
    dur1 = pulseIn(echoPin1, HIGH); // Reads the echoPin1, returns the sound wave travel time in microseconds
  
    digitalWrite(trigPin2, LOW); // Sets the trigPin2 on LOW state for 2 micro seconds
    delayMicroseconds(2);
    digitalWrite(trigPin2, HIGH); // Sets the trigPin2 on HIGH state for 10 micro seconds
    delayMicroseconds(10);
    digitalWrite(trigPin2, LOW);
    dur2 = pulseIn(echoPin2, HIGH); // Reads the echoPin2, returns the sound wave travel time in microseconds
    
    digitalWrite(trigPin3, LOW); // Sets the trigPin3 on LOW state for 2 micro seconds
    delayMicroseconds(2);
    digitalWrite(trigPin3, HIGH); // Sets the trigPin3 on HIGH state for 10 micro seconds
    delayMicroseconds(10); 
    digitalWrite(trigPin3, LOW);
    dur3 = pulseIn(echoPin3, HIGH); // Reads the echoPin3, returns the sound wave travel time in microseconds
    
    digitalWrite(trigPin4, LOW);  // Sets the trigPin4 on LOW state for 2 micro seconds
    delayMicroseconds(2); 
    digitalWrite(trigPin4, HIGH); // Sets the trigPin4 on HIGH state for 10 micro seconds
    delayMicroseconds(10);
    digitalWrite(trigPin4, LOW);
    dur4 = pulseIn(echoPin4, HIGH); // Reads the echoPin4, returns the sound wave travel time in microseconds

    digitalWrite(trigPin5, LOW); // Sets the trigPin5 on LOW state for 2 micro seconds
    delayMicroseconds(2);
    digitalWrite(trigPin5, HIGH); // Sets the trigPin5 on HIGH state for 10 micro seconds
    delayMicroseconds(10);
    digitalWrite(trigPin5, LOW);
    dur5 = pulseIn(echoPin5, HIGH); // Sets the trigPin5 on HIGH state for 10 micro seconds
    
    // Calculating the distance
    dis1 = (dur1 /2) / 29.1;
    dis2 = (dur2 /2) / 29.1;
    dis3 = (dur3 /2) / 29.1;
    dis4 = (dur4 /2) / 29.1;
    dis5 = (dur5 /2) / 29.1;
    
    delay(120);
    
    myMotor ->run(RELEASE);
    myMotor2->run(RELEASE);
    myMotor3->run(RELEASE);
    myMotor4->run(RELEASE);
  } 
}

long turn2 (long dis1, long dis2, long dis3, long dis4, long dis5) //define left function
{
  long dur1, dur2, dur3, dur4, dur5;
  while (dis2 < 6 && dis3 < 8 && dis4 > 2){
    Serial.println("turn2");
    myMotor ->run(FORWARD);
    myMotor2->run(BACKWARD);
    myMotor3->run(BACKWARD);
    myMotor4->run(FORWARD);
    myMotor ->setSpeed(30);
    myMotor2->setSpeed(30);
    myMotor3->setSpeed(200);
    myMotor4->setSpeed(200); 
    
    digitalWrite(trigPin1, LOW); // Sets the trigPin1 on LOW state for 2 micro seconds
    delayMicroseconds(2); 
    digitalWrite(trigPin1, HIGH); // Sets the trigPin1 on HIGH state for 10 micro seconds
    delayMicroseconds(10); 
    digitalWrite(trigPin1, LOW);
    dur1 = pulseIn(echoPin1, HIGH); // Reads the echoPin1, returns the sound wave travel time in microseconds
  
    digitalWrite(trigPin2, LOW); // Sets the trigPin2 on LOW state for 2 micro seconds
    delayMicroseconds(2);
    digitalWrite(trigPin2, HIGH); // Sets the trigPin2 on HIGH state for 10 micro seconds
    delayMicroseconds(10);
    digitalWrite(trigPin2, LOW);
    dur2 = pulseIn(echoPin2, HIGH); // Reads the echoPin2, returns the sound wave travel time in microseconds
    
    digitalWrite(trigPin3, LOW); // Sets the trigPin3 on LOW state for 2 micro seconds
    delayMicroseconds(2);
    digitalWrite(trigPin3, HIGH); // Sets the trigPin3 on HIGH state for 10 micro seconds
    delayMicroseconds(10); 
    digitalWrite(trigPin3, LOW);
    dur3 = pulseIn(echoPin3, HIGH); // Reads the echoPin3, returns the sound wave travel time in microseconds

    digitalWrite(trigPin4, LOW);  // Sets the trigPin4 on LOW state for 2 micro seconds
    delayMicroseconds(2); 
    digitalWrite(trigPin4, HIGH); // Sets the trigPin4 on HIGH state for 10 micro seconds
    delayMicroseconds(10);
    digitalWrite(trigPin4, LOW);
    dur4 = pulseIn(echoPin4, HIGH); // Reads the echoPin4, returns the sound wave travel time in microseconds

    digitalWrite(trigPin5, LOW); // Sets the trigPin5 on LOW state for 2 micro seconds
    delayMicroseconds(2);
    digitalWrite(trigPin5, HIGH); // Sets the trigPin5 on HIGH state for 10 micro seconds
    delayMicroseconds(10);
    digitalWrite(trigPin5, LOW);
    dur5 = pulseIn(echoPin5, HIGH); // Sets the trigPin5 on HIGH state for 10 micro seconds
  
    // Calculating the distance
    dis1 = (dur1 /2) / 29.1;
    dis2 = (dur2 /2) / 29.1;
    dis3 = (dur3 /2) / 29.1;
    dis4 = (dur4 /2) / 29.1;

    delay(120);
    
    myMotor ->run(RELEASE);
    myMotor2->run(RELEASE);
    myMotor3->run(RELEASE);
    myMotor4->run(RELEASE);
  } 
}
