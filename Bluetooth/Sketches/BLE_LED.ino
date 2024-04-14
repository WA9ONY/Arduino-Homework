/*
  LED

  This example creates a Bluetooth® Low Energy peripheral with service that contains a
  characteristic to control an LED.

  The circuit:
  - Arduino MKR WiFi 1010, Arduino Uno WiFi Rev2 board, Arduino Nano 33 IoT,
    Arduino Nano 33 BLE, or Arduino Nano 33 BLE Sense board.

  You can use a generic Bluetooth® Low Energy central app, like LightBlue (iOS and Android) or
  nRF Connect (Android), to interact with the services and characteristics
  created in this sketch.

  This example code is in the public domain.
*/

#include <ArduinoBLE.h>

BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214"); // Bluetooth® Low Energy LED Service

/*

BLEByteCharacteristic:

This is a class provided by Arduino's BLE library, which specifies that the characteristic will hold a single byte of data.
switchCharacteristic:

This is the name given to the instance of BLEByteCharacteristic. It represents a specific characteristic of a BLE service, here intended to function as a switch (likely to turn something on or off).
"19B10001-E8F2-537E-4F6C-D104768A1214":
https://fusionauth.io/dev-tools/uuid-generator

This is the UUID (Universally Unique Identifier) of the characteristic. UUIDs ensure that services and characteristics can be uniquely identified in the BLE ecosystem. The provided UUID is a custom 128-bit UUID, as opposed to standardized 16-bit or 32-bit UUIDs, allowing for custom functionality outside the predefined BLE services and characteristics.
BLERead | BLEWrite:

These are flags set for the characteristic's properties. BLERead and BLEWrite are combined using the bitwise OR operator (|), meaning the characteristic can both be read and written to by a central device (like a smartphone or computer).
BLERead allows a central device to read the characteristic's value.
BLEWrite allows a central device to write new values to the characteristic.

*/
// Bluetooth® Low Energy LED Switch Characteristic - custom 128-bit UUID, read and writable by central

BLEByteCharacteristic switchCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

const int ledPin = LED_BUILTIN; // pin to use for the LED

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // set LED pin to output mode
  pinMode(ledPin, OUTPUT);

  // begin initialization
  if (!BLE.begin()) {
    Serial.println("starting Bluetooth® Low Energy module failed!");

    while (1);
  }

  // set advertised local name and service UUID:
  BLE.setLocalName("LED");
  BLE.setAdvertisedService(ledService);

  // add the characteristic to the service
  ledService.addCharacteristic(switchCharacteristic);

  // add service
  BLE.addService(ledService);

  // set the initial value for the characeristic:
  switchCharacteristic.writeValue(0);

  // start advertising
  BLE.advertise();

  Serial.println("BLE LED Peripheral");
}

void loop() {
  // listen for Bluetooth® Low Energy peripherals to connect:
  BLEDevice central = BLE.central();

  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    // print the central's MAC address:
    Serial.println(central.address());

    // while the central is still connected to peripheral:
    while (central.connected()) {
      // if the remote device wrote to the characteristic,
      // use the value to control the LED:
      if (switchCharacteristic.written()) {
        if (switchCharacteristic.value()) {   // any value other than 0
          Serial.println("LED on");
          digitalWrite(ledPin, HIGH);         // will turn the LED on
        } else {                              // a 0 value
          Serial.println(F("LED off"));
          digitalWrite(ledPin, LOW);          // will turn the LED off
        }
      }
    }

    // when the central disconnects, print it out:
    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
  }
}
