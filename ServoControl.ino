/* Servo control for Swivl 2.0 */
#include <SoftwareSerial.h>

#include <Servo.h>

Servo servo1;
int xValue = 0;
char a;
char b;
char c;
int digit1 = 0;
int digit2 = 0;
int digit3 = 0;
int total;
int currentServoPos = 90;
void setup() {
  // put your setup code here, to run once:
  servo1.attach(3);//Tells the arduino that the data line for the servo is in pin 2
  Serial.begin(9600);
  servo1.write(currentServoPos);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.read() == 'q')//waits for a new reading from the PI
  {
    
    delay(10);//translates communication from pi to useable data
    a = Serial.read();
    delay(10);
    b = Serial.read();
    delay(10);
    c = Serial.read();
    digit1 = int(a);
    digit2 = int(b);
    digit3 = int(c);
    digit1 = digit1 - 48;
    digit2 = digit2 - 48;
    digit3 = digit3 - 48;
    digit1 = digit1 * 100;
    digit2 = digit2 * 10;
    total = digit1 + digit2 + digit3;
    digitalWrite(13, HIGH);
  
     if(total == 001)
     {
       if(currentServoPos < 180)
       {
          currentServoPos = currentServoPos + 10;
       }
     }
     else if(total == 003)
     {
        if(currentServoPos > 0)
        {
           currentServoPos = currentServoPos - 10;
        }
     }
     servo1.write(currentServoPos);

     
  }
}
