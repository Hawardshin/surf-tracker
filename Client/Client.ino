#include "Client.hpp"

void setup() {
  initializeSerial();
  initializeAll();
  Serial.println(F(SET_UP_READY_MESSAGE));
}

void loop()
{
  loopSendGPSInfo();
}

