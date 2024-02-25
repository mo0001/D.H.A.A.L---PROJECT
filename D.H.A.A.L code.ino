#include <arduino.h>
//declaring positions of trigger and echo pins
int trigger = 7;
int echo = 6;
//declaring led pin positions
int yellow = 11;
int red = 12;
int green = 13;
//position of sound pin
int sound = 10;
//initialising points of potHole,obstacle,plane
bool potHole;
bool obstacle;
bool plane;
//initialising time and distance variables
float time;
float distanceCm,Ulim,Llim;
//Detecting ground level
int detectLevel(){ 
  //code for sensor to start sending signals
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  //code for recieving signals
  time = pulseIn(echo, HIGH);
  //converting time to distance assuming speed of soundwave = 340m/s or 29cm/microseconds
  distanceCm = time / 29 / 2;
  /*dividing by 2 because time is the total time 
  i.e time taken to go + time taken to come back for the signal*/
  Llim = distanceCm - 10;
  Ulim = distanceCm + 10;
  Serial.println(Ulim);
  Serial.println(Llim);
}
void setup() {
  //pins position setup
  Serial.begin(9600);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(sound, OUTPUT);
  detectLevel();
}

void loop() {
  //detecting current level
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  time = pulseIn(echo, HIGH);
  distanceCm = time / 29 / 2;

  Serial.println(Ulim);
  Serial.println(Llim);
  Serial.println(distanceCm);

  //logic to check for pothole

  if (distanceCm > Llim && distanceCm < Ulim) //values for plane surface
  {
    plane=true;//road is clear
    obstacle=false;
    potHole=false;
  } 
  else if (distanceCm <= Llim) //values for an obstacle
  {
    plane=false;
    obstacle=true;//obstacle detected
    potHole=false;

  } 
  else if (distanceCm >= Ulim) //values for a pothole
  {
    plane=false;
    obstacle=false;
    potHole=true;//pothole detected
  }

  //Glowing leds and beeping sounds 

  if(plane==true){
    digitalWrite(green,HIGH);
    delay(75);
    digitalWrite(green,LOW);
    delay(75);
  }
  else if(obstacle==true){
    digitalWrite(yellow,HIGH);
    delay(75);
    digitalWrite(yellow,LOW);
    delay(75);
    digitalWrite(sound,HIGH);
    delay(90);
    digitalWrite(sound,LOW);
    delay(90);
  }
  else if(potHole==true){
    digitalWrite(red,HIGH);
    delay(50);
    digitalWrite(red,LOW);
    delay(50);
    digitalWrite(sound,HIGH);
    delay(20);
    digitalWrite(sound,LOW);
    delay(20);
   
  }
}