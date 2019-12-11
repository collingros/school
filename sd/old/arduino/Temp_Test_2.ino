// Libraries needed for the Transceiver
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Variable for LED
#define LED 2

// Our 2 RF24 Objects
RF24 radio(7, 8); // CE, CSN

// Address we will be using for communication
const byte address[6] = "00101";

// Function for incoming transmission


void blinkLED(){
  // Will cause the LED to blink
  digitalWrite(LED, HIGH); // Turns on LED
  delay(100); // Stays on for 0.5s
  digitalWrite(LED, LOW); // Turn off LED
  delay(100); // Stays off for 0.5s
  // Will cause the LED to blink
  digitalWrite(LED, HIGH); // Turns on LED
  delay(100); // Stays on for 0.5s
  digitalWrite(LED, LOW); // Turn off LED
  delay(100); // Stays off for 0.5s
  // Will cause the LED to blink
  digitalWrite(LED, HIGH); // Turns on LED
  delay(100); // Stays on for 0.5s
  digitalWrite(LED, LOW); // Turn off LED
  delay(100); // Stays off for 0.5s
  // Will cause the LED to blink
  digitalWrite(LED, HIGH); // Turns on LED
  delay(100); // Stays on for 0.5s
  digitalWrite(LED, LOW); // Turn off LED
  delay(100); // Stays off for 0.5s
}

void setup() {
  Serial.begin(500000);
  // For wireless communications
  radio.begin(); // Begins our radio communications
  radio.openReadingPipe(0, address[0]); // Begins the receiving side of communications
  radio.setPALevel(RF24_PA_LOW); // Sets up the Power Amplifier level
  radio.startListening(); // Listening for incoming transmission
  // For LED
  pinMode(LED, OUTPUT);
}

void loop() {
  //radio.startListening(); // Listening for incoming transmission/Turns it into a receiver
  if(radio.available()) {
    //char text[32] = "";
    float temp = 0;
    radio.read(&temp, sizeof(temp));
    //String inc_Text = String(text);
    //if(inc_Text == "Ok"){
    //blinkLED();
    if(temp <= 80){
      Serial.print("F ");
      Serial.print(temp);
      Serial.println("\xC2\xB0"); // Prints out the degree symbol
      blinkLED();
    }
    else{
      Serial.print("F ");
      Serial.print(temp);
      Serial.println("\xC2\xB0"); // Prints out the degree symbol

      // Will cause the LED to blink
      digitalWrite(LED, HIGH); // Turns on LED
      delay(500); // Stays on for 0.5s
      digitalWrite(LED, LOW); // Turn off LED
      delay(500); // Stays off for 0.5s
    }
  }
//  else{
//    // Serial.println("not receiving");
//  }
}
