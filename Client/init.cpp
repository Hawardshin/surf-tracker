
#include "sender.hpp"
void initializeSerial(){
  Serial.begin(57600);
  gps.begin(9600,SERIAL_8N1,26,27); //gps
  lora.begin(9600,SERIAL_8N1,16,17); //lora
  delay(SET_UP_DELAY);
}

void  initializeAll(){
   gps.write(GPS_BAUDRATE_57600);
  //gps.write(GPS_BAUDRATE_115200);
  delay(SET_UP_DELAY);
  gps.begin(57600,SERIAL_8N1,26,27);  //gps serial reset to 57600
//gps.begin(115200,SERIAL_8N1,26,27); //gps serial reset to 115200
  delay(SET_UP_DELAY);

  gps.write(GPS_INTERVAL_0p2);      //  fix interval. 0.2s
//gps.write(GPS_INTERVAL_0p1);      //  fix interval. 0.1s
  delay(SET_UP_DELAY);
}
