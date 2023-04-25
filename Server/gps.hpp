#ifndef GPS_HPP
# define GPS_HPP

typedef struct s_vector2{
  double x;
  double y;
}Vector2;

typedef struct s_myTime{
  int hour;
  int min;
  int sec;
  int csec;
}myTime;

typedef struct s_coordinate{
  float lat;
  float lng;
  struct s_myTime co_time;
}t_coordinaete;

typedef struct s_GPSData{ //같은 시간에 해당하는 값들을 담아놓을 구조체
  struct s_coordinate serverCoordi;
  struct s_coordinate clientCoordi;
}GPSData;

#endif
