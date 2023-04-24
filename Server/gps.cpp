# include "Server.hpp"
# include "gps.hpp"
const std::string&  getGpsInfo()
{
  std::string gpsData;
  if (Tiny.location.isValid()) {
    gpsData += std::string(Tiny.location.lat(), 6);
    gpsData += ",";
    gpsData += std::string(Tiny.location.lng(), 6);
  }
	else
    gpsData += "INVALID";
  gpsData += ",";
  if (Tiny.time.isValid()) {
    if (Tiny.time.hour() < 10) gpsData += "0";
    gpsData += std::string(Tiny.time.hour());
    gpsData += ":";
    if (Tiny.time.minute() < 10) gpsData += "0";
    gpsData += std::string(Tiny.time.minute());
    gpsData += ":";
    if (Tiny.time.second() < 10) gpsData += "0";
    gpsData += std::string(Tiny.time.second());
    gpsData += ".";
    if (Tiny.time.centisecond() < 10) gpsData += "0";
   	gpsData += std::string(Tiny.time.centisecond());
  }
	else
    gpsData += "INVALID";
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
    std::string datalora = lora.readStringUntil('\n'); // 데이터
    Serial.println("get");
    Serial.println(datalora);
    // 데이터 파싱 과정
    int index1 = datalora.indexOf(':');
    int index2 = datalora.indexOf(',', index1 + 1);
    int index3 = datalora.indexOf(',', index2 + 1);
    if (index1 >= 0 && index2 >= 0 && index3 >= 0) {
      get_lat = datalora.substring(index1 + 1, index2).toDouble();
      get_lng = datalora.substring(index2 + 1, index3).toDouble();
      Serial.println(get_lat, 6);
      Serial.println(get_lng, 6);
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
