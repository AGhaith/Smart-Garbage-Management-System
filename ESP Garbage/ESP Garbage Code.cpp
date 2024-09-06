#define BLYNK_TEMPLATE_ID "TMPL2skGZ8fWA"
#define BLYNK_TEMPLATE_NAME "test"

#include <WiFi.h>                // ESP32 WiFi library
#include <BlynkSimpleEsp32.h>    // Blynk library for ESP32
#include <ESP32Servo.h>          // Servo library for ESP32

// Variables
#define BLYNK_PRINT Serial
char auth[] = "vYn_D6RkEcs3rnOHw3m-rYfPgJFx_08k"; // Your Blynk Auth Token
char ssid[] = "Wokwi-GUEST";                           // Your WiFi SSID
char pass[] = "";                         // Your WiFi Password

// Pins
const int TRIG_PIN_IN = 12;   // GPIO for the ultrasonic sensor trigger (inside)
const int ECHO_PIN_IN = 13;   // GPIO for the ultrasonic sensor echo (inside)
const int TRIG_PIN_OUT = 21;  // GPIO for the ultrasonic sensor trigger (outside)
const int ECHO_PIN_OUT = 19;  // GPIO for the ultrasonic sensor echo (outside)
const int RED_LED_PIN = 27;   // GPIO for Red LED
const int GREEN_LED_PIN = 22; // GPIO for Green LED
const int SERVO_PIN = 18;     // GPIO for Servo

Servo myservo;  // Create a Servo object

// Variables
float garbage_level = 0;
float proximity = 0;
int full = 10;
int close_distance = 20; // Renamed to avoid conflict with the 'close' function
String fullornot = "free";
String status = "NONE";

// Function to measure distance using ultrasonic sensor
float getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  float duration = pulseIn(echoPin, HIGH);
  float distance = (duration * 0.034 / 2); // Calculate distance in cm
  Serial.print("Distance measured from pin ");
  Serial.print(trigPin);
  Serial.print(": ");
  Serial.print(distance);
  Serial.println(" cm");
  return distance;
}

// Servo control functions
void initialize_servo() {
  Serial.println("Initializing servo...");
  myservo.attach(SERVO_PIN);
  myservo.write(0);  // Start at 0 degrees
  delay(200);
  Serial.println("Servo initialized at 0 degrees.");
}

void setAngle(int angle) {
  Serial.print("Setting servo angle to ");
  Serial.print(angle);
  Serial.println(" degrees.");
  myservo.write(angle);
  delay(200);
}

// Blynk functions
BlynkTimer timer;

void sendDataToBlynk() {
  Serial.println("Sending data to Blynk...");
  Blynk.virtualWrite(0, garbage_level);
  Blynk.virtualWrite(1, fullornot);
  Blynk.virtualWrite(2, "Unavailable");
  Serial.println("Data sent to Blynk.");
}

// Check object detection
void check_object() {
  Serial.println("Checking object proximity...");
  if (proximity < close_distance) { // Object is close
    Serial.println("Object detected close. Opening bin.");
    openBin();
  } else if (status == "open") {
    Serial.println("No object detected. Closing bin.");
    closeBin();
  } else {
    Serial.println("No action taken. Bin remains closed.");
  }
}

void openBin() {
  Serial.println("Opening bin...");
  setAngle(90);
  status = "open";
  Serial.println("Bin opened.");
}

void closeBin() {
  Serial.println("Closing bin...");
  setAngle(0);
  status = "closed";
  Serial.println("Bin closed.");
}

void setup() {
  Serial.begin(115200);
  Serial.println("Starting setup...");
  Blynk.begin(auth, ssid, pass);

  pinMode(TRIG_PIN_IN, OUTPUT);
  pinMode(ECHO_PIN_IN, INPUT);
  pinMode(TRIG_PIN_OUT, OUTPUT);
  pinMode(ECHO_PIN_OUT, INPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);

  initialize_servo();
  timer.setInterval(1000L, sendDataToBlynk);
  Serial.println("Setup complete.");
}

void loop() {
  Blynk.run();
  timer.run();

  Serial.println("Loop execution started...");

  garbage_level = getDistance(TRIG_PIN_IN, ECHO_PIN_IN);
  proximity = getDistance(TRIG_PIN_OUT, ECHO_PIN_OUT);

  if (garbage_level < full) { // Bin is full
    Serial.println("Garbage bin is full.");
    // if (status == "open") closeBin();
    // fullornot = "1";
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, LOW);
  } else {
    Serial.println("Garbage bin is not full.");
    fullornot = "0";
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, HIGH);
    check_object();
  }

  Serial.println("Loop execution completed.");
    delay(1000);
}
