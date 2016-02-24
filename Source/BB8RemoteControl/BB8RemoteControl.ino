#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

RF24 radio(8,9);
const uint64_t pipe = 0xE8E8F0F0E1LL;

void setup(void)
{
  Serial.begin(9600);

  printf_begin();
  Serial.print("\n\rBB8 Remote Control\n\r");
  
  radio.begin();
  radio.setChannel(108);
  radio.setPALevel(RF24_PA_LOW);
  radio.setRetries(15, 15);
  radio.setPayloadSize(8);
  
  radio.openWritingPipe(pipe);
  radio.printDetails();
}

void loop(void)
{
  delay(1000);
  
  unsigned long toGo = millis();
  
  int numAttempts = 0;
  bool res = radio.write(&toGo, sizeof(toGo));
  if (res) {
    Serial.println("Sent <" + String(toGo) + ">!");
  } else {
    Serial.println("Failed to send <" + String(toGo) + ">");
  }
}

