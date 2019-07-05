#include <SoftwareSerial.h>
#include<Servo.h>
#include<stdlib.h>
#include<DS1620.h>

const int sensorMin = 0;
const int sensorMax = 600;

SoftwareSerial mySerial(100,6);

//DS1620
static const uint8_t RST_PIN = 7;  //pin 3 on DS1620
static const uint8_t CLK_PIN = 8; //pin 4 on DS1620
static const uint8_t DQ_PIN = 9; //pin 5 on DS1620

DS1620 ds1620(RST_PIN,CLK_PIN,DQ_PIN);

//Servo
Servo Servo1;
Servo Servo2;
Servo Servo3;
//Sonar
const int pingPin = 11;

void setup() {
Serial.begin(9600);
delay(100);
ds1620.config();     
pinMode(1,OUTPUT);
pinMode(6,OUTPUT);
digitalWrite(6,HIGH);
mySerial.begin(9600);
mySerial.write(12);
  

}

void loop() {

int sensorReading = analogRead(A0);
  // map the sensor range to a range of four options:
  int range = map(sensorReading, sensorMin, sensorMax, 0, 3);

  switch (range) {
    case 0:    // your hand is on the sensor
      Serial.println("ON");
      Servo1.attach(10);
      Servo2.attach(12);
      Servo3.attach(13);
      break;
    case 1:    // your hand is close to the sensor
      Serial.println("OFF");
      off();
      case 2:
      Serial.println("Normal");//few inches from sensor
      break;
    case 3:    // your hand is nowhere near the sensor
      Serial.println("Temperature On");
      temperature();
  }
  delay(1);     
long duration, inches, cm;

  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  Serial.print(inches);
  Serial.print( "in, " );
  Serial.print(cm);
  Serial.print( "cm" );
  Serial.println();

  Servo1.write(80);
  Servo2.write(87);
  Servo3.write(60);
  delay(814);
  
  Servo1.write(90);
  Servo2.write(90);
  Servo3.write(90);
  delay(814);
  
  Servo1.write(100);
  Servo2.write(93);
  Servo3.write(95);
  delay(726);  

  if((inches>0)||(inches<50)){
    
     Servo1.detach();
     Servo2.detach();
     Servo3.detach();
     long duration, inches, cm;

  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  Serial.print(inches);
  Serial.print( "in, " );
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
     }
  else if((inches==0)||(inches>50)){
      Servo1.attach(10);
      Servo2.attach(12);
      Servo3.attach(13);

     }
  
}

long microsecondsToInches(long microseconds) {
 // According to Parallax's datasheet for ultrasonic sensing, there 
 // are 73.746 microseconds per inch (i.e. sound travels at 1130 feet 
  // per second).  This gives the distance travelled by the ping, 
  // outbound and return, so we divide by 2 to get the distance of the 
  // obstacle.See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
void off(){
  Serial.println( "THE DEVICE IS OFF" );
     Servo1.detach();
     Servo2.detach();
     Servo3.detach();    
     loop();
}
 void temperature(){
     Servo1.detach();
     Servo2.detach();
     Servo3.detach();    
  const float temp_c = ds1620.temp_c();
const float temp_f = temp_c*9/5.0+32 ;
if (temp_f>78){
  mySerial.println( "             HOT" );
  tone(1,1000,250);
}
else if (temp_f<72){
  mySerial.println( "             COLD" );
  tone(1,100,250);
}
else if ((temp_f>72)||(temp_f<78)){
  mySerial.println("                      ");
 noTone(1);
}
Serial.print(temp_f,1);
Serial.println( "  F" );
mySerial.print(temp_f,1);
mySerial.println( "   F" );
Serial.print(temp_c,1);
Serial.println( "  C" );
loop();

}
