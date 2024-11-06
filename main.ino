// Pin definitions
#define TRIG_PIN 9         // Trigger pin of the HC-SR04 ultrasonic sensor
#define ECHO_PIN 10         // Echo pin of the HC-SR04 ultrasonic sensor
#define GREEN_LED 7         // Green LED for distances > maxDistance
#define YELLOW_LED 6        // Yellow LED for distances between minDistance and maxDistance
#define RED_LED 4          // Red LED for distances < minDistance
#define JOYSTICK_Y A0       // Y-axis of the joystick for dynamic adjustment of distance ranges

// Variables for distance measurement
long duration;             // Time taken for the pulse to travel to and from the object
int distance;              // Calculated distance in centimeters

void setup() {
  // Set pin modes for ultrasonic sensor and LEDs
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(JOYSTICK_Y, INPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  // Initialize serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Measure distance using the ultrasonic sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Read the duration of the echo pulse
  duration = pulseIn(ECHO_PIN, HIGH);
  // Calculate distance in centimeters
  distance = duration * 0.034 / 2;

  // Read joystick position for dynamic threshold adjustment
  int joystickValue = analogRead(JOYSTICK_Y);
  
  int thre = map (joystickValue,0,1023,10,20) ;
  int thre2 =thre+20;
  int thre3 =thre2+20;

  // Debug output to the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm, thre: ");
  Serial.println(thre);


  // Control LEDs based on the measured distance
  if (distance < thre) {
    // RED LED
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, HIGH);
  } else if (distance > thre && distance <= thre2) {
    // Yellow LED 
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(RED_LED, LOW);
  } else if (distance <= thre3) {
    // GREEN LED 
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, LOW);
  }else{
    //ALL is LOW
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, LOW);
  }
                  

}
