#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9          
#define SS_PIN          10        

const int soundSensorPin = A0;
const int redPin = 5;
const int greenPin = 7;
const int yellowPin = 6;

MFRC522 mfrc522(SS_PIN, RST_PIN);
void setup() {
Serial.begin(9600);		
while (!Serial);		
	SPI.begin();			
	mfrc522.PCD_Init();		
	pinMode(redPin, OUTPUT);
	pinMode(yellowPin, OUTPUT);
	pinMode(greenPin, OUTPUT);
	mfrc522.PCD_DumpVersionToSerial();
	Serial.println(F("Scan now..."));
}

void loop() {
	// Red light
        digitalWrite(redPin, HIGH);
        digitalWrite(yellowPin, LOW);
        digitalWrite(greenPin, LOW);
        delay(1000); // Red light for 5 seconds
        // Yellow light
        digitalWrite(redPin, LOW);
        digitalWrite(yellowPin, HIGH);
        digitalWrite(greenPin, LOW);
        delay(1000); // Yellow light for 2 seconds
        // Green light
        digitalWrite(redPin, LOW);
        digitalWrite(yellowPin, LOW);
        digitalWrite(greenPin, HIGH);
        delay(1000); // Green light for 5 seconds
        if (  !mfrc522.PICC_IsNewCardPresent()) {
          return;
        }
        int sensorValue = analogRead(soundSensorPin);
        Serial.print("Sound Sensor Value: ");
        Serial.println(sensorValue);
      
      if (sensorValue > 35) {
	      if (  mfrc522.PICC_ReadCardSerial()) {
          	mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
          	digitalWrite(redPin, HIGH); // Red light on
          	delay(4000); // Hold red for 2 seconds
        	digitalWrite(redPin, LOW); // Red light off
          	digitalWrite(yellowPin, HIGH); // Yellow light on
          	delay(2500); // Hold yellow for 1 second
          	digitalWrite(yellowPin, LOW); // Yellow light off
          	digitalWrite(greenPin, HIGH); // Green light on
          	delay(8000); // Hold green for 3 seconds
          	digitalWrite(greenPin, LOW); // Green light of
          	return;
          	delay(1000);
          	}
      }  
}
