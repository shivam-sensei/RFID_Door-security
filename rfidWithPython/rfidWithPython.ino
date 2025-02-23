//  * Typical pin layout used:
//  * -----------------------------------------------------------------------------------------
//  *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
//  *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
//  * Signal      Pin          Pin           Pin       Pin        Pin              Pin
//  * -----------------------------------------------------------------------------------------
//  * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
//  * SPI SS      SDA(SS)      10            53        D10        10               10
//  * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
//  * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
//  * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9          // Reset pin
#define SS_PIN 10          // Slave select pin
#define SOLENOID_PIN 4     // GPIO pin to control the solenoid lock
#define redLED 6
#define greenLED 7
#define irSensor 5

int pyread;

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance

// Define the specific UID (replace with your tag's UID)
byte mastercardUID[4] = {0xB3, 0xC5, 0xE3, 0xC9};  // Replace with your tag's UID

void setup() {
  SPI.begin();                 // Init SPI bus
  mfrc522.PCD_Init();          // Init MFRC522
  Serial.begin(115200);        // Start serial communication
  pinMode(SOLENOID_PIN, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(irSensor, INPUT);
  digitalWrite(SOLENOID_PIN, HIGH); // Ensure solenoid is initially off

  Serial.println("Place your tag to unlock the solenoid.");

}

void loop() {
  int sensorStatus=digitalRead(irSensor); //read from IR Sensor
  if (sensorStatus == LOW){
    Serial.println("Motion Detected at IR Sensor");
    digitalWrite(SOLENOID_PIN, LOW); // Activate solenoid
    delay(2000);                     // Keep solenoid open for 2 seconds
    digitalWrite(SOLENOID_PIN, HIGH); // Deactivate solenoid
  } else {
    digitalWrite(SOLENOID_PIN, HIGH);
  }
  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent()) return;

  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) return;

  // Print UID to the serial monitor
  Serial.print("Scanned UID: ");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    if (i < mfrc522.uid.size - 1) Serial.print(":");
  }
  Serial.println();

  //check for Master Card
  if (isAuthorized(mfrc522.uid.uidByte, mfrc522.uid.size)) {
    // Serial.println("Access Granted: Unlocking solenoid...");
    digitalWrite(SOLENOID_PIN, LOW); // Activate solenoid
    delay(2000);                     // Keep solenoid open for 2 seconds
    digitalWrite(SOLENOID_PIN, HIGH); // Deactivate solenoid
    // Serial.println("Solenoid locked.");
  }

  pyread=Serial.read();

  while (!Serial.available()) {}
  String response = Serial.readString();
  response.trim();
  
  if (response == "True") {
    digitalWrite(greenLED, HIGH);
    digitalWrite(SOLENOID_PIN, LOW); // Activate solenoid
    delay(2000);                     // Keep solenoid open for 2 seconds
    digitalWrite(SOLENOID_PIN, HIGH); // Deactivate solenoid
    digitalWrite(greenLED, LOW);
  } else {
    digitalWrite(redLED, HIGH); 
    delay(100);                     
    digitalWrite(redLED, LOW); 
    delay(100);       
    digitalWrite(redLED, HIGH); 
    delay(100);                     
    digitalWrite(redLED, LOW); 
    delay(100);    
  }
  mfrc522.PICC_HaltA(); // Halt PICC
  mfrc522.PCD_StopCrypto1(); // Stop encryption on the PCD

}

// Function to check if UID matches the master card UID
bool isAuthorized(byte *uid, byte length) {
  for (byte i = 0; i < length; i++) {
    if (uid[i] != mastercardUID[i]) {
      return false;
    }
  }
  return true;
}

