/*  Getting BPM to draw patterns by using stepper and servo motor. 
 *  Using PulseSensor library, Stepper library and Servo library.

------------------------------------------Use this sketch to--------------------------------------------
1)  Display user's live BPM, Beats Per Minute, in Arduino's native Serial Monitor.
2)  Use BPM to change the servo and stepper motor functions, thereby changing the pattern drawn on paper with linkages.
3)  Blink red LED on PIN 12 when patterns are being drawn after detecting a BPM.
4)  Blink green LED on PIN 7 when ready to read another heart beat. 
--------------------------------------------------------------------------------------------------------*/

#include <Stepper.h>      //Includes the Stepper motor library
#include <Servo.h>        //Includes the Servo motor library

#define USE_ARDUINO_INTERRUPTS true     // Set-up low-level interrupts for most acurate BPM math
#include <PulseSensorPlayground.h>      // Includes the PulseSensorPlayground Library 

//  Variables
const int PulseWire = A0;     // PulseSensor signal wire connected to ANALOG PIN 0
const int LED13 = 13;         // The on-board Arduino LED, close to PIN 13
int Threshold = 550;          // Determine which Signal to "count as a beat" and which to ignore
int green = 7;                // Green LED connected to PIN 7 to indicate ready to read pulse
int red = 12;                 // Red LED connected to PIN 12 to indicate wait time until next reading 
              
const int stepsPerRevolution = 600;     // Indicated stepper motor steps per revolution to be 600
Stepper myStepper(stepsPerRevolution,5,10,6,11);      // Stepper motor connected to PINs 5, 10, 6 and 11 
Servo myservo;      // Creates servo object to control a servo                               
PulseSensorPlayground pulseSensor;      // Creates an instance of the PulseSensorPlayground object called pulseSensor

int pos = 0;      // Variable to store the servo position

void setup() {  
   
  myservo.attach(9);      // Attaches the servo on pin 9 to the servo object
  myStepper.setSpeed(60);     // Sets the stepper speed to 60
  Serial.begin(9600);     // For Serial Monitor
  
  // Configure the PulseSensor object, by assigning our variables to it 
  pulseSensor.analogInput(PulseWire);     // Takes signal from pulse sensor as input
  pulseSensor.blinkOnPulse(LED13);      // Automatically blink Arduino's LED with heartbeat
  pulseSensor.setThreshold(Threshold);
  // Double-check the pulseSensor object was created and began seeing a signal 
  if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");      // This prints one time at Arduino power-up,  or on Arduino reset  
    }
  pinMode(green, OUTPUT);     // Assigns the pin connected to green LED as output
  digitalWrite(green, HIGH);      // Glows the green LED
  pinMode(red, OUTPUT);     // Assigns the pin connected to red LED as output
  digitalWrite(red, LOW);      // Dims the red LED
  }

void loop() {
  int myBPM = pulseSensor.getBeatsPerMinute();      // Calls function on our pulseSensor object that returns BPM as an "int"
                                                    // myBPM hold this BPM value now
  int repeat = 0;     // Assigns repeat value as 0                                             
  if (pulseSensor.sawStartOfBeat()) {     // Constantly test to see if "a beat happened" 
    Serial.print("Waiting for heartbeat! ");      //If test is "true", print a message "a heartbeat happened"
    }
  if (myBPM >= 40 && myBPM <= 60) {     // If heartbeat value is between 40 and 60 BPM
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
    for (repeat = 0; repeat <3; repeat +=1) {       //For 3 repeats
      Serial.print("♥  A HeartBeat Happened ! ");   
      Serial.print("BPM below 60: ");
      Serial.println(myBPM);
      for (pos = 0; pos <= 160; pos += 1) {     // Servo motor goes from 0 degrees to 160 degrees - clockwise
        myStepper.setSpeed(10);     // Stepper motor rotates at a speed of 10
        myStepper.step(10);     // Stepper motor moves in steps of 10
        myservo.write(pos);     //Servo motor moves from 0 degrees to 160 degrees
        delay(5);
        }
      for (pos = 160; pos >= 0; pos -= 1) {     // Servo motor goes from 160 degrees to 0 degrees - clockwise
        myStepper.setSpeed(10);
        myStepper.step(10);
        myservo.write(pos);             
        delay(5);    
        }
      }
    }
  else if (myBPM >= 61 && myBPM <= 80) {      // If heartbeat value is between 61 and 80 BPM
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
    for (repeat = 0; repeat <3; repeat +=1) { 
      Serial.println("♥  A HeartBeat Happened ! ");
      Serial.print("BPM above 60: ");
      Serial.println(myBPM);
      for (pos = 0; pos <= 180; pos += 2) {
        myStepper.setSpeed(10);
        myStepper.step(25);
        myservo.write(pos);
        delay(5);
        }
      for (pos = 180; pos >= 0; pos -= 2) { 
        myStepper.setSpeed(10);
        myStepper.step(-25);
        myservo.write(pos);          
        delay(5);        
        }
      }
     }
  else if (myBPM >= 81 && myBPM <= 100) {     // If heartbeat value is between 81 and 100 BPM
     digitalWrite(green, LOW);
     digitalWrite(red, HIGH);
     for (repeat = 0; repeat <2; repeat +=1) {
       Serial.println("♥  A HeartBeat Happened ! ");
       Serial.print("BPM above 80: ");
       Serial.println(myBPM);
       for (pos = 0; pos <= 180; pos += 1) {
         myStepper.setSpeed(10);
         myStepper.step(20);
         myservo.write(pos);
         delay(5);
         }
       for (pos = 180; pos >= 0; pos -= 1) { 
         myStepper.setSpeed(10);
         myStepper.step(-20);
         myservo.write(pos);           
         delay(5);    
         }
       }
     }
  else if (myBPM >= 101 && myBPM <= 120) {      // If heartbeat value is between 101 and 120 BPM
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
    for (repeat = 0; repeat <3; repeat +=1) {
      Serial.println("♥  A HeartBeat Happened ! ");
      Serial.print("BPM above 100: ");
      Serial.println(myBPM);
      for (pos = 0; pos <= 180; pos += 1) {     // Servo motor goes from 0 degrees to 180 degrees - clockwise
        myStepper.setSpeed(10);
        myStepper.step(10);
        myservo.write(pos);
        delay(5);
        }
       for (pos = 180; pos >= 0; pos -= 1) {      // Servo motor goes from 180 degrees to 0 degrees - anticlockwise
        myStepper.setSpeed(10);
        myStepper.step(-10);
        myservo.write(pos);
        delay(5);  
        }
      }
    }
  else {
    digitalWrite(green, HIGH);
    digitalWrite(red, LOW);
    }
  delay(20); 
  }


  
