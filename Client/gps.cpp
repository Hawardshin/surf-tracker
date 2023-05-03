#include "Client.hpp"

// string version //
//lat = 6, lng = 6, hour =2, minite =2, second=2,centisecond =2
//총 데이터 길이만 하면 6+6+2+2+2+2 = 20
//데이터 길이 20으로 초기화 해서 그 값을 계속 보내는 것으로 한다.
// const t_coordinaete&  getGpsInfo()
// {
//   std::string gpsData(20);
//   if (Tiny.location.isValid()) {
//     gpsData.replace(0,6,std:: to_string (Tiny.location.lat()).substr(0,6));
//     gpsData.replace(6,6,std:: to_string (Tiny.location.lng()).substr(0,6));
//   }
// 	else
//     gpsData.replace(0,12,"XXXXXXXXXXXX");
//   if (Tiny.time.isValid()) {
//     gpsData[12] = Tiny.time.hour() /10 + '0';
//     gpsData[13] = Tiny.time.hour() %10 + '0';
//     gpsData[14] = Tiny.time.minute() /10 + '0';
//     gpsData[15] = Tiny.time.minute() % 10 + '0';
//     gpsData[16] = Tiny.time.second() /10 + '0';
//     gpsData[17] = Tiny.time.second() % 10 + '0';
//     gpsData[18] = Tiny.time.centisecond() /10 + '0';
//     gpsData[19] = Tiny.time.centisecond() % 10 + '0';
//   }
// 	else
//     gpsData.replace(12,8,"XXXXXXXX");
// 	return(gpsData);
// }

static void  parseData(t_coordinaete &data){
  if (Tiny.location.isValid()){
    data.isvaildCoord = true;
    data.lat = Tiny.location.lat();
    data.lng = Tiny.location.lng();
  }//if time over the day you must check!
  if (Tiny.time.isValid()){
    data.isvaildTime = true;
    data.co_time.hour = Tiny.time.hour();
    data.co_time.min = Tiny.time.minute();
    data.co_time.sec = Tiny.time.second();
    data.co_time.csec = Tiny.time.centisecond();
  }
}
//개선점
// GPS값을 100ms마다 한번이라서 버리는 데이터가 꽤 될텐데 그 데이터들을 평균을 구하는 방식을 생각해보기
void  loopSendGPSInfo(){
  bool isInputAvailable = false;
  unsigned long previousMicros = micros(); // 이전 시간 저장
  t_coordinaete mydata;
  memset(&toSend,0,sizeof(t_coordinaete));
  while (micros() - previousMicros < 100000) // 100ms 마다 한번 (100,000 마이크로초)
  {
    if (gps.available() && Tiny.encode(gps.read()))
        isInputAvailable = true;
  }
  if(isInputAvailable == true)
     parseData(mydata);
  lora.write((byte*)&mydata,sizeof(mydata));
}
