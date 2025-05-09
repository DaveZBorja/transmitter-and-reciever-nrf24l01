#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 8);  // CE, CSN
const byte address[6] = "00001";

// Relays (LOW trigger)
const int redRelay = 3;
const int yellowRelay = 4;
const int greenRelay = 5;

void setup() {
  Serial.begin(9600);

  pinMode(redRelay, OUTPUT);
  pinMode(yellowRelay, OUTPUT);
  pinMode(greenRelay, OUTPUT);
  allRelaysOff();

  // NRF24
  radio.begin();
  radio.openReadingPipe(1, address);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    char receivedCommand[32] = "";
    radio.read(&receivedCommand, sizeof(receivedCommand));

    Serial.print("Received command: ");
    Serial.println(receivedCommand);

    if (strcmp(receivedCommand, "YELLOW") == 0) {
      digitalWrite(redRelay, HIGH);   // Papatayin ang red
      digitalWrite(yellowRelay, LOW); // I-on ang yellow
      digitalWrite(greenRelay, HIGH); // Papatayin ang green
    }
    else if (strcmp(receivedCommand, "RED") == 0) {
      digitalWrite(yellowRelay, HIGH); // Papatayin ang yellow
      digitalWrite(redRelay, LOW);     // I-on ang red
      digitalWrite(greenRelay, HIGH);  // Papatayin ang green
    }
    else if (strcmp(receivedCommand, "GREEN") == 0) {
      // Gamitin ang default na green state
      digitalWrite(redRelay, HIGH);
      digitalWrite(yellowRelay, HIGH);
      digitalWrite(greenRelay, LOW);
    }
    else if (strcmp(receivedCommand, "STOP") == 0) {
      allRelaysOff();
    }
    else if (strcmp(receivedCommand, "RESUM") == 0) {
      // Resuming logic if needed
    }
  }
}

void allRelaysOff() {
  digitalWrite(redRelay, HIGH);
  digitalWrite(yellowRelay, HIGH);
  digitalWrite(greenRelay, HIGH);
}
