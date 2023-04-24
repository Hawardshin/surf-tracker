#include "Client.hpp"
//lat = 6, lng = 6, hour =2, minite =2, second=2,centisecond =2
//총 데이터 길이만 하면 6+6+2+2+2+2 = 20
//데이터 길이 20으로 초기화 해서 그 값을 계속 보내는 것으로 한다.
void  sendGpsInfo()
{
  if (Tiny.location.isValid()) {
    lora.print(Tiny.location.lat(), 6);
    lora.print(Tiny.location.lng(), 6);
  }
	else
    lora.print(F("XXXXXXXXXXXX"));
  std::string string_time(8);
  if (Tiny.time.isValid()) {
      int hour = Tiny.time.hour();
      int min = Tiny.time.minute();
      int sec = Tiny.time.second();
      int csec = Tiny.time.centisecond();
      string_time[0] = hour /10 + '0';
      string_time[1] = hour % 10 + '0';
      string_time[2] = min/10 + '0';
      string_time[3] = min % 10 + '0';
      string_time[4] = sec / 10 + '0';
      string_time[5] = sec % 10 + '0';
      string_time[6] = csec /10 + '0';
      string_time[7] = csec % 10 + '0';
      lora.print(string_time);
  }
  else
    lora.print(F("XXXXXXXXXXXX"));
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
    sendGPSInfo();
  else
    lora.println("noData");
}
