
/* These are defined and will be the pins allocated for our
 * LED and Motion Sensor output
 */
#define LED 5
#define motionIn 6

// Variables to hold state of motion sensor and val it produces
int motionState = LOW;
int val = 0;

// Function to blink LED while there is motion detected
void motionBlink(){
  digitalWrite(LED, HIGH);
  delay(250);
  digitalWrite(LED, LOW);
  delay(250);
}

void setup() {
  Serial.begin(9600);
  // Setting the pin allocated to LED as output and motion sensor as in
  pinMode(LED, OUTPUT);
  pinMode(motionIn, INPUT);
}

void loop() {
  // Reads our input from the sensor(LOW = no motion, HIGH = motion detected)
  val = digitalRead(motionIn);
  if(val == HIGH){
    digitalWrite(LED, HIGH);
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
    digitalWrite(LED, LOW);
    if(motionState == HIGH){
      Serial.println("There is no movement detected.");
      motionState = LOW;
    }
  }
}
