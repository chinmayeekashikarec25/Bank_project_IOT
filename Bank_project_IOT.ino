#include <Servo.h>

const int irPin = 2;
const int buzzerPin = 8;

Servo myServo;

bool customerPresent = false;

void setup() {
  Serial.begin(9600);

  pinMode(irPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  myServo.attach(7);
  myServo.write(0);

  Serial.println("System Ready");
  Serial.println("Servo at 0 degrees");
}

void loop() {

  int sensorState = digitalRead(irPin);

  // Customer detected
  if (sensorState == LOW) {

    if (!customerPresent) {

      Serial.println("Customer Arrived");

      // Buzzer beep once
      digitalWrite(buzzerPin, HIGH);
      delay(500);
      digitalWrite(buzzerPin, LOW);

      myServo.write(90);
      Serial.println("Servo moved to 90 degrees");

      customerPresent = true;
    }

    // Keep updating while customer is present
    Serial.println("Customer Still There");
  }

  // Customer left
  else {

    if (customerPresent) {

      Serial.println("Customer Left");

      myServo.write(0);
      Serial.println("Servo moved to 0 degrees");

      customerPresent = false;
    }
  }

  delay(500);
}