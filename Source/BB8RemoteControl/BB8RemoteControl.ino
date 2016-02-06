#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

RF24 radio(8,9);
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

void setup(void)
{
  Serial.begin(9600);

  printf_begin();
  Serial.print("\n\rBB8 Remote Control\n\r");

  radio.begin();

  radio.openWritingPipe(pipes[0]);
  radio.printDetails();
}

void loop(void)
{
  delay(1000);
  
  unsigned long toGo = millis();

  bool ok = radio.write(&toGo, sizeof(unsigned long));
  if (ok) {
    Serial.println("Sent <" + String(toGo) + ">!");
  } else {
    Serial.println("Failed to send <" + String(toGo) + ">");
  }
}

