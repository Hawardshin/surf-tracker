#include "preprocessor.hpp"

double averaging(double avg, double newdata, double n) { //평균필터 알고리즘 -> 실시간 평균
  return (avg * (n - 1) / n + newdata / n);
}

void setup() {
  myservo.write(cent);
  Serial.print("ready1");
}

void loop()
{

  boolean newData = true;
	// boolean newData = false;
	// for (unsigned long start = millis(); millis() - start < 100;)
	// {
	// 	while (gps.available())
	// 	{
	// 		if (Tiny.encode(gps.read()))
	// 		{
	// 			newData = true;
	// 			Serial.print("ready2");
	// 		}
	// 	}
	// }

  if (newData == true)
  {
  // newData = false;
    if (lora.available())
    {
      String datalora = lora.readStringUntil('\n'); // 데이터
      Serial.println("get");
      Serial.println(datalora);
      // 데이터 파싱과정
      int index1 = datalora.indexOf(':');
      int index2 = datalora.indexOf(',', index1 + 1);
      int index3 = datalora.indexOf(',', index2 + 1);
      get_lat = datalora.substring(index1 + 1, index2).toDouble();
      get_lng = datalora.substring(index2 + 1, index3).toDouble();
//      Serial.println(get_lat, 6);
//      Serial.println(get_lng, 6);
/////////////////////////////////////////////////////////////////////////////////////////
//받은데이터 계산해서 두벡터사이 각도 계산
      v2x = get_lat - fixed_lat;
      v2y = get_lng - fixed_lng;
      v1 = sqrt(pow(v1x, 2) + pow(v1y, 2));
      v2 = sqrt(pow(v2x, 2) + pow(v2y, 2));
      double upper = (v1x * v2y) - (v1y * v2x); //분모
      double theta = asin(upper / (v1 * v2)); // + 반시계 , - 시계
      theta = (theta * 180) / M_PI;
    //  Serial.println(theta);
    }
  }
  else
  {
     Serial.println("thisnodata");
  }
}


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
