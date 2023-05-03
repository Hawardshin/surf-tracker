//ToDo :
// 1.parse gps to lat lng and time with struct
# include "Server.hpp"
# include "gps.hpp"

double getRadian(Vector2& c_vec, Vector2& s_vec){
  //받은데이터 계산해서 두벡터사이 각도 계산
  v2x = get_lat - fixed_lat;
  v2y = get_lng - fixed_lng;
  v1 = sqrt(pow(v1x, 2) + pow(v1y, 2));
  v2 = sqrt(pow(v2x, 2) + pow(v2y, 2));
  double upper = (v1x * v2y) - (v1y * v2x); //분모
  double theta = asin(upper / (v1 * v2)); // + 반시계 , - 시계
  theta = (theta * 180) / M_PI;
}
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

void  parseNetworkData(t_coordinaete &mydata){
   if(lora.available()){
    Serial.print("NET WORK PARSE!!\n");
    lora.readBytes(mydata,sizeof(mydata));
    myreadyQueue.push(mydata);
    printData(mydata);
  }
}
void  printTime(const myTime& time){
  Serial.print("time : ");
  Serial.print(time.hour);
  Serial.print(" : ");
  Serial.print(time.min);
  Serial.print(" : ");
  Serial.print(time.sec);
  Serial.print(" : ");
  Serial.print(time.csec);
  Serial.print("\n");
;}

void  printData(const t_coordinaete &data){
  printTime(data.co_time);
  Serial.print("Location : ");
  Serial.print("lat : ");
  Serial.print(data.lat);
  Serial.print(",lng : ");
  Serial.print(data.lng);
  Serial.print("\n");
}

void  serverGPSInfo(){
  t_coordinaete ClientData;
  t_coordinaete ServerData;
  memset(ClientData, 0, sizeof(t_coordinaete));
  memset(ServerData, 0, sizeof(t_coordinaete));
  bool isInputAvailable = false;
  unsigned long previousMicros = micros(); // 이전 시간 저장
  while (micros() - previousMicros < 100000) // 100ms 마다 한번 (100,000 마이크로초)
  {
    parseNetworkData(ClientData);
    if (gps.available() && Tiny.encode(gps.read()))
        isInputAvailable = true;
  }
  if(isInputAvailable == true){
    parseData(ServerData);
  }
  else{
    Serial.print("notGood");
  }
}


// void parseNetworkData(){
//   if (lora.available()) {
//     // char buffer[21]; // 버퍼 크기는 데이터 크기에 맞게 조절 가능
//     // int size = lora.readBytesUntil('\n', buffer, sizeof(buffer));//이거 전부 다 20이어야한다.
//     // if (size > 0) {
//     // buffer[size] = '\0'; // 문자열 종료 문자 삽입
//     // // 데이터 파싱과정
//     // parseGpsInfo(buffer);
//     // char* ptr = buffer;
//   }
//   }
//   else {
//     Serial.println("no data");
//   }
// }
