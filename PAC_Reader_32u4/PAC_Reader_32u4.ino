/*
 
  PAC code RFID Reader (PAC ONEPROX GS3-MT)
  For Arduino Leonardo 32u4 boards (Pro Micro)
  
  Use:
  pin 7 for LED
  pin 8 for Sig
  Gnd to Gnd

  Library:
  https://github.com/paulo-raca/YetAnotherArduinoPcIntLibrary
  
*/

#include <SoftwareSerial.h>
#include <Keyboard.h>
#include <elapsedMillis.h>

SoftwareSerial mySerial(8, 11);
elapsedMillis timeElapsed;
elapsedMillis timeElapsedLED;
elapsedMillis LEDflash;

const int LEDpin = 7;
unsigned int interval = 2000;
unsigned int intervalLED = 250;
boolean stopReading = false;
boolean falseReading = false;
boolean resetStart = true;
byte variable[1000];
byte index = 0;
String fullCode = "";

void setup()
{
  Serial.begin(57600);
  //Keyboard.begin();
  while (!Serial) {
    ;
  }
  mySerial.begin(9600);//9600
  pinMode(LEDpin, OUTPUT);
  digitalWrite(LEDpin, HIGH);
}

void loop()
{
  if (mySerial.available()) {
    byte b = mySerial.read();
    variable[index++] = b;
    if (index == 17 && !stopReading) { //
      if ((variable[0] == 0x18) && (variable[1] == 0x18) && (variable[2] == 0x18)) {
        stopReading = true;
        digitalWrite(LEDpin, LOW);
        showResults();
        timeElapsed = 0;
        resetStart = true;
      }
      else {
        stopReading = true;
        timeElapsed = 0;
        resetStart = true;
        falseReading = true;
      }
    }
  }
  if (timeElapsed > interval && resetStart) {
    resetStart = false;
    falseReading = false;
    digitalWrite(LEDpin, HIGH);
    stopReading = false;
    index = 0;
    timeElapsed = 0;
  }
  if (timeElapsedLED > intervalLED && falseReading) {
    digitalWrite(LEDpin, !digitalRead(LEDpin));
    timeElapsedLED = 0;
  }
}

void showResults() {
  /*
    Serial.print(variable[0], HEX);
    Serial.print(variable[1], HEX);
    Serial.print(variable[2], HEX);
    Serial.print(variable[3], HEX);
    Serial.print(variable[4], HEX);
    Serial.print(variable[5], HEX);
    Serial.print(variable[6], HEX);
    Serial.print(variable[7], HEX);
    Serial.print(variable[8], HEX);
    Serial.print(variable[9], HEX);
    Serial.print(variable[10], HEX);
    Serial.print(variable[11], HEX);
    Serial.print(variable[12], HEX);
    Serial.print(variable[13], HEX);
    Serial.print(variable[14], HEX);
    Serial.print(variable[15], HEX);
    Serial.println(variable[16], HEX);
  */
  for (uint8_t i = 0; i < 17; i++) {
    if (variable[i] < 16) fullCode += "0";
    fullCode += String(variable[i], HEX);
    fullCode.toUpperCase();
  }

  Serial.println(fullCode);
  //Keyboard.println(fullCode);
  fullCode = "";
}