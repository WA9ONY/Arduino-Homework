const int ledPin = LED_BUILTIN;  // the number of the LED pin

void setup() {
  pinMode(ledPin, OUTPUT);  // initialize the LED pin as an output
  Serial.begin(9600);  // initialize serial communication at 9600 bps
}

void loop() {
  for (int delayTime = 10; delayTime <= 30; delayTime++) {
    // Blink at varying frequencies
    blink(ledPin, delayTime, delayTime);

    // Print the frequency to the serial monitor
    Serial.print("Frequency: ");
    Serial.print(1000.0 / (2 * delayTime));  // calculate and print the frequency
    Serial.println(" Hz");
  }
}

void blink(int pin, int onTime, int offTime) {
  digitalWrite(pin, HIGH);  // turn the LED on
  delay(onTime);           // wait for the specified time
  digitalWrite(pin, LOW);   // turn the LED off
  delay(offTime);           // wait for the specified time
}
