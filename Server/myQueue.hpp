#ifndef MYQUEUE_HPP
# define MYQUEUE_HPP
# include "gps.hpp"
class myQueue{
  public :
    static const int DATA_SIZE = 1000;
    void  push(t_coordinaete &a);
    bool  isfull();
    t_coordinaete data[DATA_SIZE];
  private :
    int begin_idx;//데이터 읽으면 늘어나는 인덱스
    int end_idx;//데이터를 푸쉬할 수 있는 공간 인덱스
};
#endif
