#include "global.hpp"

HardwareSerial lora(1); //lora 통신방법
HardwareSerial gps(2);
TinyGPSPlus Tiny;
Servo myservo;
myQueue myreadyQueue;
