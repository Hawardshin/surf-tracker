#ifndef GLOBAL_HPP
# define GLOBAL_HPP
# include <string>
# include <HardwareSerial.h>
# include <TinyGPSPlus.h>
# include <TinyGPS++.h>
#include <ESP32_Servo.h>
#include <math.h>
extern HardwareSerial gps;
extern HardwareSerial lora;
extern TinyGPSPlus Tiny; //gps libarry
extern Servo myservo;

# define GPS_BAUDRATE_57600 "$PMTK251,57600*2C\r\n"
# define GPS_BAUDRATE_115200 "$PMTK251,115200*1F\r\n"
# define GPS_INTERVAL_0p2 "$PMTK220,200*2C\r\n" //0.2s
# define GPS_INTERVAL_0p1 "$PMTK220,100*2F\r\n" //0.1s
# define SET_UP_DELAY 1000
# define SET_UP_READY_MESSAGE "SET UP READY"
# define INIT_DEGREE 86
#endif
