#include "sender.hpp"

void  sendGPSInfo_String()
{
  String gpsData;
  
  if (Tiny.location.isValid()) {
    gpsData += String(Tiny.location.lat(), 6);
    gpsData += ",";
    gpsData += String(Tiny.location.lng(), 6);
  } else {
    gpsData += "INVALID";
  }
  gpsData += ",";
  if (Tiny.time.isValid()) {
    if (Tiny.time.hour() < 10) gpsData += "0";
    gpsData += String(Tiny.time.hour());
    gpsData += ":";
    if (Tiny.time.minute() < 10) gpsData += "0";
    gpsData += String(Tiny.time.minute());
    gpsData += ":";
    if (Tiny.time.second() < 10) gpsData += "0";
    gpsData += String(Tiny.time.second());
    gpsData += ".";
    if (Tiny.time.centisecond() < 10) gpsData += "0";
    gpsData += String(Tiny.time.centisecond());
  } else {
    gpsData += "INVALID";
  }
  
  lora.println(gpsData);
}

void sendGPSInfo()
{
  
  if (Tiny.location.isValid()) {
    lora.print(F("Location: "));
    lora.print(Tiny.location.lat(), 6);
    lora.print(",");
    lora.print(Tiny.location.lng(), 6);
    lora.print(" ");
  } else {
    lora.print(F("Location: INVALID "));
  }
  
  if (Tiny.time.isValid()) {
    lora.print(F("Time: "));
    if (Tiny.time.hour() < 10) lora.print(F("0"));
    lora.print(Tiny.time.hour());
    lora.print(F(":"));
    if (Tiny.time.minute() < 10) lora.print(F("0"));
    lora.print(Tiny.time.minute());
    lora.print(F(":"));
    if (Tiny.time.second() < 10) lora.print(F("0"));
    lora.print(Tiny.time.second());
    lora.print(F("."));
    if (Tiny.time.centisecond() < 10) lora.print(F("0"));
    lora.print(Tiny.time.centisecond());
    lora.println();
  } else {
    lora.println(F("Time: INVALID"));
  }
} 

void  loopSendGPSInfo(){
  bool isInputAvailable = false;
  unsigned long previousMicros = micros(); // 이전 시간 저장
  while (micros() - previousMicros < 100000) // 100ms 마다 한번 (100,000 마이크로초)
  {
    if (gps.available() && Tiny.encode(gps.read()))
        isInputAvailable = true;
  }
  if(isInputAvailable == true)
    sendGPSInfo_String();
    // sendGPSInfo();
  else
    lora.println("noData");
}
