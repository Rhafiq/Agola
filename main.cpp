#include <Arduino.h>

/*
  Project: ESP32 Bluetooth Mobile Robot
  Board:
  - ESP32 Dev Module (Node32 Lite)
    https://my.cytron.io/p-node32-lite-wifi-and-bluetooth-development-kit
 */

#include <BluetoothSerial.h>
#include <ESP32Servo.h>
BluetoothSerial btSerial;
#define BT_NAME "AgolaESP32-A" // Set bluetooth name

Servo myservo;
Servo myservo2;

int pos = 0;

long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

int trigPin = 23;      // trig pin of HC-SR04
int echoPin = 22;     // Echo pin of HC-SR04

int revleft4 = 32;       //REVerse motion of Left motor
int fwdleft5 = 33;       //ForWarD motion of Left motor
int revright6 = 25;      //REVerse motion of Right motor
int fwdright7 = 26;      //ForWarD motion of Right motor

boolean btConnected = false;
char key, previousKey;
long previousMillis = 0;
int timeout = 1000;

void setup()
{
 delay(random(500,2000));   // delay for random time
  Serial.begin(115200);
  pinMode(revleft4, OUTPUT);      // set Motor pins as output
  pinMode(fwdleft5, OUTPUT);
  pinMode(revright6, OUTPUT);
  pinMode(fwdright7, OUTPUT);
  
  myservo.attach(2,500,2400);
   myservo2.attach(4,500,2400);
   
  pinMode(trigPin, OUTPUT);         // set trig pin as output
  pinMode(echoPin, INPUT); 
  btSerial.begin(BT_NAME);
  
  Serial.println("ESP32 Bluetooth Mobile Robot");
  Serial.println();


}

void loop()
{
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  Serial.println(distance);

  
 if (distance > 19)            
  {
    digitalWrite(fwdright7, HIGH);                    // move forward
    digitalWrite(revright6, LOW);
    digitalWrite(fwdleft5, HIGH);                                
    digitalWrite(revleft4, LOW);                                                       
  }

 else if (distance < 18)
  {
    digitalWrite(fwdright7, LOW);  //Stop                
    digitalWrite(revright6, LOW);
    digitalWrite(fwdleft5, LOW);                                
    digitalWrite(revleft4, LOW);
    delay(500);
    digitalWrite(fwdright7, LOW);      //movebackword         
    digitalWrite(revright6, HIGH);
    digitalWrite(fwdleft5, LOW);                                
    digitalWrite(revleft4, HIGH);
    delay(1000);
    digitalWrite(fwdright7, LOW);  //Stop                
    digitalWrite(revright6, LOW);
    digitalWrite(fwdleft5, LOW);                                
    digitalWrite(revleft4, LOW);  
    delay(100);  
    digitalWrite(fwdright7, HIGH);       
    digitalWrite(revright6, LOW);   
    digitalWrite(revleft4, LOW);                                 
    digitalWrite(fwdleft5, LOW);  
    delay(1000);
  }

 

  else if (btSerial.available()) {
    previousMillis = millis();
    
    char inChar = (char)btSerial.read();

    if (btConnected == false) {
      btConnected = true;
      Serial.println("Bluetooth connected.");
    }

    if (inChar >= '0' && inChar <= '9') {
      key = inChar;
      if (key != previousKey) {
        
        switch (key) {
          case '0':
            Serial.println("Robot stop.");
            digitalWrite(fwdright7, LOW);  //Stop                
    digitalWrite(revright6, LOW);
    digitalWrite(fwdleft5, LOW);                                
    digitalWrite(revleft4, LOW);
            break;

          case '1':
            Serial.println("Robot move forward.");
            digitalWrite(fwdright7, HIGH);  //Stop                
    digitalWrite(revright6, LOW);
    digitalWrite(fwdleft5, HIGH);                                
    digitalWrite(revleft4, LOW);
            break;

          case '2':
            Serial.println("Robot move backward.");
           digitalWrite(fwdright7, LOW);  //Stop                
    digitalWrite(revright6, HIGH);
    digitalWrite(fwdleft5, LOW);                                
    digitalWrite(revleft4, HIGH);
            break;

          case '3':
            Serial.println("Robot turn left.");
           digitalWrite(fwdright7, LOW);  //Stop                
    digitalWrite(revright6, LOW);
    digitalWrite(fwdleft5, HIGH);                                
    digitalWrite(revleft4, LOW);
            break;

          case '4':
            Serial.println("Robot turn right.");
         digitalWrite(fwdright7, HIGH);  //Stop                
    digitalWrite(revright6, LOW);
    digitalWrite(fwdleft5, LOW);                                
    digitalWrite(revleft4, LOW);
            break;

          case '5':
            Serial.println("Arm Right");
            for (pos = 0; pos <= 180; pos +=1)
            {
              myservo.write(pos);
            delay(15);
            }
            break;

          case '6':
            Serial.println("Arm Left");
            for (pos = 180; pos >= 0; pos -=1)
            {
              myservo2.write(pos);
            delay(15);
            }
            break;

          case '7':
            Serial.println("both arm");
            for (pos = 180; pos >= 0; pos -=1)
            {
              myservo.write(pos);
              myservo2.write(pos);
            delay(15);
            }
            break;
        }
      }
       else{
       digitalWrite(fwdright7, LOW);  //Stop                
    digitalWrite(revright6, LOW);
    digitalWrite(fwdleft5, LOW);                                
    digitalWrite(revleft4, LOW);
      }
    }
  }
}

 