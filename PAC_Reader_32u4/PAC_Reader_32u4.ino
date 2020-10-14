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

int LEDpin = 7;
unsigned int interval = 2000;
boolean delayTest = false;
byte variable[1000];
byte index = 0;
String fullCode = "";

void setup()
{
  //Serial.begin(57600);
  Keyboard.begin();
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
    if (index == 17 && !delayTest) { //
      delayTest = true;
      digitalWrite(LEDpin, LOW);
      showResults();
      timeElapsed = 0;
    }
  }
  if (timeElapsed > interval) {
    digitalWrite(LEDpin, HIGH);
    delayTest = false;
    index = 0;
    timeElapsed = 0;
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

  //Serial.println(fullCode);
  //Serial.println("");
  Keyboard.println(fullCode);
  fullCode = "";
}