#include <MKRWAN.h>

LoRaModem modem;

String appKey = ""; // app key from TTN
String appEui = "0000000000000000";
String devEui = ""; // your device ID

void setup() {
  // initialize serial
  Serial.begin(9600);
  while(!Serial);

  Serial.println("Serial connected");

  // initialize modem
  if(!modem.begin(EU868)) {
    Serial.println("Unable to init modem :(");
    while(1) {}
  }

  // print out device ID and firmware version
  Serial.print("ID: ");
  Serial.println(modem.deviceEUI());

  Serial.print("Firmware: ");
  Serial.println(modem.version());

  // connect to TTN
  if(!modem.joinOTAA(appEui, appKey)) {
    Serial.println("Failed to join network");
    while(1) {}
  }
  
  Serial.println("Connected to the network!");
}

void loop() {
  // write a short message
  String message = "hello world";

  // send the data to TTN
  modem.beginPacket();
  modem.print(message);
  if (!modem.endPacket(false)) {
    Serial.println("failed to send packet :(");
  }

  // wait a minute before sending the next packet
  delay(60000);
}
