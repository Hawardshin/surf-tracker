#ifndef GPS_HPP
# define GPS_HPP

typedef struct s_vector2{
  double x;
  double y;
}Vector2;

typedef struct s_coordinate{
  double lat;
  double lng;
}t_coordinaete;

typedef struct s_GPSData{
  struct s_coordinate serverCoordi;
  struct s_coordinate clientCoordi;
}GPSData;

#endif
