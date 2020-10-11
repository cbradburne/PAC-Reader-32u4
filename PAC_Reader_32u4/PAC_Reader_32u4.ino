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

#include <YetAnotherPcInt.h>
#include <Keyboard.h>
#include <elapsedMillis.h>

elapsedMillis LED1millis;

unsigned int LED1_Interval = 2000;
unsigned volatile long reader1 = 0;
unsigned volatile long reader2 = 0;
unsigned volatile long reader3 = 0;
unsigned volatile long reader4 = 0;
volatile int reader1Count = 0;
const int LEDpin = 7;

void reader1One(bool pinstate) {
  if (pinstate == LOW && reader1Count <= 32) {
    reader1Count++;
    reader1 = reader1 << 1;
    reader1 |= 1;
  }
  else if (pinstate == HIGH && reader1Count <= 32) {
    reader1Count++;
    reader1 = reader1 << 1;
  }
  else if (pinstate == LOW && reader1Count > 32 && reader1Count <= 64) { // && reader1Count <= 64
    reader1Count++;
    reader2 = reader2 << 1;
    reader2 |= 1;
  }
  else if (pinstate == HIGH && reader1Count > 32 && reader1Count <= 64) { // && reader1Count <= 64
    reader1Count++;
    reader2 = reader2 << 1;
  }
  else if (pinstate == LOW && reader1Count > 64 && reader1Count <= 96) { // && reader1Count <= 64
    reader1Count++;
    reader3 = reader3 << 1;
    reader3 |= 1;
  }
  else if (pinstate == HIGH && reader1Count > 64 && reader1Count <= 96) { // && reader1Count <= 64
    reader1Count++;
    reader3 = reader3 << 1;
  }
  else if (pinstate == LOW && reader1Count > 96 && reader1Count <= 128) { // && reader1Count <= 64
    reader1Count++;
    reader4 = reader4 << 1;
    reader4 |= 1;
  }
  else if (pinstate == HIGH && reader1Count > 96 && reader1Count <= 128) { // && reader1Count <= 64
    reader1Count++;
    reader4 = reader4 << 1;
  }
  else if (pinstate == LOW && reader1Count > 128) {
    reader1Count++;
  }
  else if (pinstate == HIGH && reader1Count > 128) {
    reader1Count++;
  }
}

void setup() {
  Serial.begin(115200);
  Keyboard.begin();
  pinMode(LEDpin, OUTPUT);
  pinMode(8, INPUT_PULLUP);
  PcInt::attachInterrupt(8, reader1One, CHANGE);
  reader1 = 0;
  reader2 = 0;
  reader3 = 0;
  reader4 = 0;
  reader1Count = 0;
  digitalWrite(LEDpin, HIGH);
}

void loop() {
  /*
  if (reader1Count == 1) {
    //digitalWrite(7, LOW);
    LED1millis = 0;
  }
  else if (reader1Count == 1242){
    Serial.println(reader1 /2);
    Serial.println(reader2);
    reader1 = 0;
    reader2 = 0;
    reader1Count = 0;
  }

  if (LED1millis >= LED1_Interval){
    digitalWrite(7, HIGH);
  }

  */
    
  if (reader1Count == 1) {
    digitalWrite(LEDpin, LOW);
    LED1millis = 0;
  }
  else if (reader1Count == 1242){
    Serial.println(reader1);
    Serial.println(reader2);
    Serial.println(reader3);
    Serial.println(reader4);
    Keyboard.println(reader1);
    reader1 = 0;
    reader2 = 0;
    reader3 = 0;
    reader4 = 0;
    reader1Count = 0;
  }

  if (LED1millis >= LED1_Interval){
    digitalWrite(LEDpin, HIGH);
  }
}
