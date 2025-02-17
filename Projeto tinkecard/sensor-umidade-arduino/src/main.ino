const int motorPin = 10;
const int ledRedPin = 9;
const int ledGreenPin = 8;
const int soilSensorPin = A0;

unsigned long previousMillis = 0;
const long interval = 500;

void setup() {
  pinMode(motorPin, OUTPUT);
  pinMode(ledRedPin, OUTPUT);
  pinMode(ledGreenPin, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("Sistema iniciado. Monitorando sensor de umidade...");
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    int soilSensorValue = analogRead(soilSensorPin);
    Serial.print("Umidade detectada: ");
    Serial.println(soilSensorValue);

    int motorSpeed = calculateMotorSpeed(soilSensorValue);
    analogWrite(motorPin, motorSpeed);
    updateLEDs(soilSensorValue);

    Serial.print("Velocidade do motor (PWM): ");
    Serial.println(motorSpeed);
    Serial.println("-------------------------");
  }
}

int calculateMotorSpeed(int soilSensorValue) {
  soilSensorValue = constrain(soilSensorValue, 0, 875);
  return map(soilSensorValue, 0, 875, 255, 0);
}

void updateLEDs(int soilSensorValue) {
  if (soilSensorValue < 300) {
    digitalWrite(ledRedPin, HIGH);
    digitalWrite(ledGreenPin, LOW);
  } else if (soilSensorValue >= 700) {
    digitalWrite(ledRedPin, LOW);
    digitalWrite(ledGreenPin, HIGH);
  } else {
    digitalWrite(ledRedPin, LOW);
    digitalWrite(ledGreenPin, LOW);
  }
}