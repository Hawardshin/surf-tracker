#include "global.hpp"

double averaging(double avg, double newdata, double n) { //평균필터 알고리즘 -> 실시간 평균
  return (avg * (n - 1) / n + newdata / n);
}

void setup() {
  myservo.write(cent);
  Serial.print("ready1");
}

void loop()
{
}
