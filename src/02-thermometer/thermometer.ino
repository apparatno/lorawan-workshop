#include <MKRWAN.h>

LoRaModem modem;

int pin = A3;

String appKey = "";
String appEui = "0000000000000000";
String devEui = "";

void setup() {
  Serial.begin(9600);
  while(!Serial);

  Serial.println("LoRaWAN Thermomether 2000 loading...");

  if (!modem.begin(EU868)) {
    Serial.println("Failed to initialize modem");
    while(1) {}
  }

  Serial.println("Modem initialized");

  Serial.print("ID: ");
  Serial.println(modem.deviceEUI());

  Serial.print("Firmware: ");
  Serial.println(ARDUINO_FW_VERSION);

  if (!modem.joinOTAA(appEui, appKey)) {
    Serial.println("Failed to join network");
    while(1) {}
  }

  Serial.println("connected to the network!");
}

void loop() {
  // read the voltage on the pin
  int value = analogRead(pin);

  // convert to volts (use 3300 if connected to 3.3V)
  float v = value * (5000 / 1024.0);

  // convert to degrees Celcius
  float temp = (v - 500) / 10.0;
  
  Serial.print("Sending temp: ");
  Serial.println(temp);
  
  // send the value to TTN
  modem.beginPacket();
  modem.print(temp);
  if (!modem.endPacket(false)) {
    Serial.println("failed to send message");
    return;
  }
  Serial.println("message sent");

  delay(60000);
}
