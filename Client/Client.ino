#include "Client.hpp"

void setup() {
  initializeSerial();
  initializeAll();
}

void loop(){
  loopSendGPSInfo();
}

