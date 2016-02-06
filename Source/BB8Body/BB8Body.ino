#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

RF24 radio(9,10);
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };
char output[100];

void setup(void)
{
  Serial.begin(9600);
  
  printf_begin();
  Serial.print("\n\rBB8 Body Control\n\r");

  radio.begin();

  radio.openReadingPipe(0, pipes[0]);
  radio.printDetails();
  radio.startListening();
}

void loop(void)
{
  unsigned long dest = 0.0;
  if (radio.available()) {
    bool ok = radio.read(&dest, sizeof(unsigned long));
    if (ok) {
      Serial.println(String(dest));
    }
    else {
      Serial.println("Failed reading");
    }
  }

  delay(100);
}

