#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

RF24 radio(9,53);
const uint64_t pipe = 0xE8E8F0F0E1LL;
char output[100];

/*
void setup(void)
{
  Serial.begin(9600);
  
  printf_begin();
  Serial.print("\n\rBB8 Body Control\n\r");

  radio.begin();
  radio.setChannel(108);
  radio.setPALevel(RF24_PA_LOW);
  radio.setPayloadSize(8);
  radio.setRetries(15, 15);
  radio.openReadingPipe(1, pipe);
  radio.printDetails();
  radio.startListening();
}

void loop(void)
{
  unsigned long started_waiting_at = millis();
    bool timeout = false;
    while ( ! radio.available() && ! timeout )
      if (millis() - started_waiting_at > 200 )
        timeout = true;

    // Describe the results
    if ( timeout )
    {
      printf("Failed, response timed out.\n\r");
    }
    else
    {
      // Grab the response, compare, and send to debugging spew
      unsigned long got_time;
      radio.read( &got_time, sizeof(unsigned long) );

      // Spew it
      printf("Got response %lu, round-trip delay: %lu\n\r",got_time,millis()-got_time);
    }

    // Try again 1s later
    delay(1000);
}
*/

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
