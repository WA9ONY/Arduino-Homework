const int ledPin = LED_BUILTIN;  // the number of the LED pin

void setup() {
  pinMode(ledPin, OUTPUT);  // initialize the LED pin as an output
}

void loop() {
  // Blink at 1 Hz (1 second on, 1 second off)
  blink(ledPin, 1000, 1000);

  // Blink at 5 Hz (200ms on, 200ms off)
  blink(ledPin, 200, 200);

  // Blink at 10 Hz (100ms on, 100ms off)
  blink(ledPin, 100, 100);

  // Blink at 20 Hz (50ms on, 50ms off)
  blink(ledPin, 50, 50);

  // Blink at 50 Hz (20ms on, 20ms off)
  blink(ledPin, 20, 20);

  // Blink at 100 Hz (10ms on, 10ms off)
  blink(ledPin, 10, 10);
}

void blink(int pin, int onTime, int offTime) {
  digitalWrite(pin, HIGH);  // turn the LED on
  delay(onTime);           // wait for the specified time
  digitalWrite(pin, LOW);   // turn the LED off
  delay(offTime);           // wait for the specified time
}
