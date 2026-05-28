/*
Bluetooth control light on (1) & off (0)

Wire Connection
🔵 HC-05 to Arduino:
HC-05 Pin	Arduino Uno
VCC	5V
GND	GND
TXD	D10 (Software RX)
RXD	D11 (via 1k + 2k voltage divider to avoid 5V damage)
💡 Light / LED:
LED/Relay	Arduino
+ (Anode)	D8
– (Cathode or GND)	GND
*/


#include <SoftwareSerial.h>

#define BT_RX 10   // Connect to HC-05 TX
#define BT_TX 11   // Connect to HC-05 RX
#define LIGHT_PIN 8

SoftwareSerial BT(BT_RX, BT_TX);

void setup() {
  pinMode(LIGHT_PIN, OUTPUT);
  digitalWrite(LIGHT_PIN, LOW);  // Light off initially

  Serial.begin(9600);  // Debug
  BT.begin(9600);      // HC-05 default baud rate

  Serial.println("Bluetooth Light Control Ready.");
}

void loop() {
  if (BT.available()) {
    char cmd = BT.read();
    Serial.print("Received: ");
    Serial.println(cmd);

    if (cmd == '1') {
      digitalWrite(LIGHT_PIN, HIGH);  // Turn ON
      BT.println("Light ON");
    } else if (cmd == '0') {
      digitalWrite(LIGHT_PIN, LOW);   // Turn OFF
      BT.println("Light OFF");
    } else {
      BT.println("Invalid command");
    }
  }
}
