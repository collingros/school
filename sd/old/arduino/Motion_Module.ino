/* This program is for the motion sensor module of our Notification System (ANS: Anywhere Notification System, name pending
 *  approval), there will be a transceiver (model: nRF24LO1) that will transmit to another transceiver attached to our central
 *  unit which is a Raspberry Pi 3 Model B. Motion sensor will have retriggered enabled which means that as long as there is
 *  motion in front of the sensor the alarm will keep sending out a notification.
 *  There will be 3 LEDs to indicate that there are certain stages active:
 *  - Green LED will indicate that the module is powered on
 *  - Yellow LED will indicate that there is a wireless connection set up
 *  - White LED will blink when the motion sensor is triggered
 */

// Libraries for our transceiver
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Our 2 Radio Objects
RF24 radio(7, 8); // CE, CSN

#define gLED 3 // Green LED
#define yLED 4 // Yellow LED
#define wLED 5 // White LED
#define motionIn 6

// Address we will be using for communication
const byte address[][6] = "10000";

// Variables to store motion sensor values
int val = 0;
int motionState = LOW;

// Function to blink LED while there is motion detected
void motionBlink(){
  digitalWrite(wLED, HIGH);
  delay(250);
  digitalWrite(wLED, LOW);
  delay(250);
}

/* Function will detect if there is motion and save state of motion into motionState var
 * this motionState will be transmitted to the receiver which will then use that to notify
 * user, LOW means all clear and HIGH means there is motion detected.
 */
int motionDetection(){
  val = digitalRead(motionIn);
  if(val == HIGH){
    digitalWrite(wLED, HIGH);
    if(motionState == LOW){
      /* Motion sensor is set to retrigger so while there is motion
       * detected the "INTRUDER" message will be triggered and LED will blink
       */
      while(val == HIGH){
        Serial.println("INTRUDER!!!");
        motionBlink();
        val = digitalRead(motionIn);
      }
      motionState = HIGH;
    }
  }
  if(val == LOW){
    digitalWrite(wLED, LOW);
    if(motionState == HIGH){
      Serial.println("There is no movement detected.");
      motionState = LOW;
    }
  }
  return(motionState);
}

 void setup() {
  Serial.begin(500000);
  // Wireless Communications initiation
  radio.begin(); // Begins our radio communications
  radio.openWritingPipe(address[0]); // Begins the trasmission side of communications
  radio.setPALevel(RF24_PA_LOW); /* Sets the Power Ambeplifier level
                                  * (Higher level means our modules range will increase) */

  pinMode(gLED, OUTPUT);
  pinMode(yLED, OUTPUT);
  pinMode(wLED, OUTPUT);
  pinMode(motionIn, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

}
