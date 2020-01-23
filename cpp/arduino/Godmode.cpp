#include "Godmode.h"
#include "HardwareSerial.h"


unsigned long millisValue = 0;

unsigned long millis() {
  return millisValue++;
}

unsigned long micosValue = 0;
unsigned long micros() {
  return micosValue++;
}

void delay(unsigned long millis) {
  return;
}

void delayMicroseconds(unsigned long micros) {
  return;
}

void randomSeed(unsigned long seed)
{
  return;
}

long random(long vmax)
{
  return 0;
}

long random(long vmin, long vmax)
{
  return 0;
}

void digitalWrite(unsigned char pin, unsigned char val) {
  return;
}

int digitalRead(unsigned char pin) {
  return 0;
}

void analogWrite(unsigned char pin, int val) {
  return;
}

int analogRead(unsigned char pin) {
  return 0;
}

void attachInterrupt(uint8_t interrupt, void ISR(void), uint8_t mode) {
  return;
}

void detachInterrupt(uint8_t interrupt) {
  return;
}


