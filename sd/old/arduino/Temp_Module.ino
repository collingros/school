/* This program is the Receiver Part of our testing for the Temperature Sensors (model: DS18B20) with wireless implementations.
 * The program takes in an analog signal from our sensor and converts it into readable degress which can be
 * chosen, (celcius, fahrenheit or kelvin). There is then a wireless transmission using a transceiver (model: nRF24L01)
 * of the temperature and a character array to another arduino with a Transceiver (model: nRF24L01). The array will indicate
 * if the temperature is below our threshold, if not there will be a warning character array.
 */

// Libraries for our thermo sensor
#include <OneWire.h>
#include <DallasTemperature.h>

// Name of our thermo sensor
#define Thermo_Sensor 2

// Temp Sensors
OneWire oneWire(Thermo_Sensor);
DallasTemperature sensors(&oneWire);

// Libraries for our transceiver
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Our 2 Radio Objects
RF24 radio(7, 8); // CE, CSN

// Address we will be using for communication
const byte address[6] = "00101";

// float variables that will be used to store our temperatures
float Celcius = 0;
float Fahrenheit = 0;
float temp = 0;

/* Function to calculate the temperature
 * - Will calculate temperature in both celcius and fahrenheit
 * and will print out both temperature values
 */
float Calc_Temp(){
  sensors.requestTemperatures(); 
  Celcius = sensors.getTempCByIndex(0);
  Fahrenheit = sensors.toFahrenheit(Celcius);
  Serial.print(" C  ");
  Serial.print(Celcius);
  Serial.print("\xC2\xB0"); // Prints out the degree symbol
  Serial.print(" F  ");
  Serial.print(Fahrenheit);
  Serial.println("\xC2\xB0"); // Prints out the degree symbol
  //delay(1000);
  // Return the variable you want your units in
  return(Fahrenheit);
}

// Function to see if temp is over our trigger point
void trigger_Alarm(float t){
  if(t <= 86){
    const char text[] = "Ok";
    radio.write(&text, sizeof(text));
    Serial.println(text);
    delay(1000);
  }
  if(t > 86){
    const char text[] = "TEMP IS DANGEROUSLY HIGH!!!";
    radio.write(&text, sizeof(text));
    Serial.println(text);
    delay(1000);
  }
}
 
void setup(void)
{
  Serial.begin(500000);
  sensors.begin();
  // Wireless Communications
  radio.begin(); // Begins our radio communications
  radio.openWritingPipe(address[0]); // Begins the trasmission side of communications
  radio.setPALevel(RF24_PA_LOW); // Sets the Power Ambeplifier level
  radio.stopListening(); // Will be set as a transmitter
}

void loop(void)
{ 
  // Calls function to calculate temp
  temp = Calc_Temp();
  trigger_Alarm(temp);
  delay(5);
  //radio.stopListening(); // Turns it into a transmitter
  radio.write(&temp, sizeof(temp));
}
