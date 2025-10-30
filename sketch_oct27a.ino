#include <Servo.h>

Servo myservo;

const int hallPin = A0; // Analog pin connected to VOUT of AD22151
const int servoPin = 2; //Positive pin for motor

float refVoltage = 5.00;  //base voltage
float voltage = 0;

//Values for sensor and servo motor
int sensorValue = 0;
int servoPos = 0;

// Thresholds for activation
float lowThreshold = 1.;
float highThreshold = 2.150;


void setup() {
  Serial.begin(9600);
  myservo.attach(servoPin);
  Serial.println("AD22151 Hall Sensor with Motor Control");
  delay(500);
}



void loop() {
  
  // Read sensor
  sensorValue = analogRead(hallPin);
  voltage = sensorValue * (refVoltage / 1023.0);


  // ---- SERIAL OUTPUT ----
  Serial.print("Raw: ");
  Serial.print(sensorValue);
  Serial.print("  |  Voltage: ");
  Serial.print(voltage, 3);
  Serial.print(" V");

  // Detect polarity (relative to neutral) and print to the terminal
  if (voltage > 1.750)
    Serial.print("  → South Pole (Positive Field)");
  else if (voltage < 2.150)
    Serial.print("  → North Pole (Negative Field)");
  else
    Serial.print("  → No Significant Field");

  // ---- MOTOR CONTROL ----
  if (voltage < lowThreshold) {
    Serial.println("  | Motor ON (Below 1.8V)");
    myservo.write(120);
    delay(500);
  } 
  else if (voltage > highThreshold) {
    Serial.println("  | Motor ON (Above 2.0V)");
    myservo.write(120);
    delay(500);

  } else {
    Serial.println("  | Motor OFF");
    myservo.write(90);
    delay(15);

  }

  delay(200);
}
