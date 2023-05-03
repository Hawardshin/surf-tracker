#ifndef GPS_HPP
# define GPS_HPP
# include "global.hpp"

typedef struct s_vector2{
  double x;
  double y;
}Vector2;

typedef struct s_myTime{
  uint8_t hour;
  uint8_t min;
  uint8_t sec;
  uint8_t csec;
}myTime;

typedef struct s_coordinate{
  bool    isvaildTime;
  bool    isvaildCoord;
  double  lat;
  double  lng;
  struct s_myTime co_time;
}t_coordinaete;


void  loopSendGPSInfo();
# endif
