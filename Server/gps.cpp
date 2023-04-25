# include "Server.hpp"
# include "gps.hpp"

//ToDo :
// 1.parse gps to lat lng and time with struct
// 2.make func can see in serial my data easy to see

// isue
//1. make my data to float (it only 6 digit so fast calc) is this good ? to calc????
// 4.

const t_coordinaete&  parseGpsInfo(char* s){
  t_coordinaete retData;
  retData.lat = atof()
}

t_coordinaete parseMyGpsInfo(){

}
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

void parseNetworkData(){
  if (lora.available()) {
    char buffer[21]; // 버퍼 크기는 데이터 크기에 맞게 조절 가능
    int size = lora.readBytesUntil('\n', buffer, sizeof(buffer));//이거 전부 다 20이어야한다.
    if (size > 0) {
    buffer[size] = '\0'; // 문자열 종료 문자 삽입
    // 데이터 파싱과정
    parseGpsInfo(buffer);
    char* ptr = buffer;

  }
    // std::string datalora = lora.readStringUntil('\n'); // 데이터
    // Serial.println("get");
    // Serial.println(datalora);
    // // 데이터 파싱 과정
    // int index1 = datalora.indexOf(':');
    // int index2 = datalora.indexOf(',', index1 + 1);
    // int index3 = datalora.indexOf(',', index2 + 1);
    // if (index1 >= 0 && index2 >= 0 && index3 >= 0) {
    //   get_lat = datalora.substring(index1 + 1, index2).toDouble();
    //   get_lng = datalora.substring(index2 + 1, index3).toDouble();
    //   Serial.println(get_lat, 6);
    //   Serial.println(get_lng, 6);
    }
  }
  else {
    Serial.println("no data");
  }
}

const std::string&  serverGPSInfo(){
  bool isInputAvailable = false;
  unsigned long previousMicros = micros(); // 이전 시간 저장
  while (micros() - previousMicros < 100000) // 100ms 마다 한번 (100,000 마이크로초)
  {
    if (gps.available() && Tiny.encode(gps.read()))
        isInputAvailable = true;
  }
  if(isInputAvailable == true){
    const std::string &ret = getGpsInfo();
  }
  else{
    Serial.print("notGood");
  }
}
