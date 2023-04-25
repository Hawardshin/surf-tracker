#include "Client.hpp"
//lat = 6, lng = 6, hour =2, minite =2, second=2,centisecond =2
//총 데이터 길이만 하면 6+6+2+2+2+2 = 20
//데이터 길이 20으로 초기화 해서 그 값을 계속 보내는 것으로 한다.
const std::string&  getGpsInfo()
{
  std::string gpsData(20);
  if (Tiny.location.isValid()) {
    gpsData.replace(0,6,std:: to_string (Tiny.location.lat()).substr(0,6));
    gpsData.replace(6,6,std:: to_string (Tiny.location.lng()).substr(0,6));
  }
	else
    gpsData.replace(0,12,"XXXXXXXXXXXX");
  if (Tiny.time.isValid()) {
    gpsData[12] = Tiny.time.hour() /10 + '0';
    gpsData[13] = Tiny.time.hour() %10 + '0';
    gpsData[14] = Tiny.time.minute() /10 + '0';
    gpsData[15] = Tiny.time.minute() % 10 + '0';
    gpsData[16] = Tiny.time.second() /10 + '0';
    gpsData[17] = Tiny.time.second() % 10 + '0';
    gpsData[18] = Tiny.time.centisecond() /10 + '0';
    gpsData[19] = Tiny.time.centisecond() % 10 + '0';
  }
	else
    gpsData.replace(12,8,"XXXXXXXX");
	return(gpsData);
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
    lora.println(getGpsInfo());
  else
    lora.println(std::string(F("NNNNNNNNNNNNNNNNNNNN")));
}
