
#include "preprocessor.hpp"

// static const int servoPin = 4;
// int cent = 86;


// int pre_sec = 0 ;

// double this_lat = 0;
// double this_lng = 0 ;

// double get_lat = 0;
// double get_lng = 0;

// double avg_lat = 0;
// double avg_lng = 0;


// double avg_lat_get = 0;
// double avg_lng_get = 0;
// double n_averaging = 1;
// double fixed_lat = 37.632104;
// double fixed_lng = 127.076876;
// double moved_lat = 37.632198;
// double moved_lng = 127.076407;
// double v1x = moved_lat - fixed_lat;
// double v1y = moved_lng - fixed_lng;
// double v2x = 0;
// double v2y = 0;
// double v1, v2;
double averaging(double avg, double newdata, double n) { //평균필터 알고리즘 -> 실시간 평균
  return (avg * (n - 1) / n + newdata / n);
}
void setup() {
  Serial.begin(115200);
  gps.begin(9600, SERIAL_8N1, 26, 27); //gps
  lora.begin(9600, SERIAL_8N1, 16, 17); //lora
  //Serial1.begin(9600,SERIAL_8N1,9,10); //
  pinMode (servoPin, OUTPUT);
  myservo.attach(servoPin);
  myservo.write(cent);
  Serial.print("ready1");
}

void loop()
{

  boolean newData = true;
//boolean newData = false;
//  for (unsigned long start = millis(); millis() - start < 100;)
//  {
//    while (gps.available())
//    {
//      if (Tiny.encode(gps.read()))
//      {
//        newData = true;
//        Serial.print("ready2");
//      }
//    }
//  }

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
     // Serial.println(theta);
    }
   // Serial.println("this");
   // displayInfo();
//    if (this_lat != 0 && this_lng != 0)
//    {
//      avg_lat = averaging(avg_lat, this_lat, n_averaging);
//      avg_lng = averaging(avg_lng, this_lng, n_averaging);
//      Serial.print(avg_lat, 6);
//      Serial.print(",");
//      Serial.println(avg_lng, 6);
//      Serial.println(n_averaging);
//      n_averaging++;
//    }
  }
  else
  {
     Serial.println("thisnodata");
  }
}


void displayInfo()
{
  Serial.print(F("Location: "));
  if (Tiny.location.isValid())
  {
    this_lat = Tiny.location.lat();
    this_lng = Tiny.location.lng();

    Serial.print(Tiny.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(Tiny.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F(" "));
  if (Tiny.time.isValid())
  {
    if (Tiny.time.hour() < 10) Serial.print(F("0"));
    Serial.print(Tiny.time.hour());
    Serial.print(F(":"));
    if (Tiny.time.minute() < 10) Serial.print(F("0"));
    Serial.print(Tiny.time.minute());
    Serial.print(F(":"));
    if (Tiny.time.second() < 10) Serial.print(F("0"));
    Serial.print(Tiny.time.second());
    Serial.print(F("."));
    if (Tiny.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(Tiny.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.println();
}
