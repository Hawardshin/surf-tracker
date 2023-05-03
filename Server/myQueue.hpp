#ifndef MYQUEUE_HPP
# define MYQUEUE_HPP
# include "gps.hpp"
# include "global.hpp"
//TODO
//1. 서버 GPS 푸쉬
//2. 클라이언트 GPS를 이용해 찾기.!
//3. 현재 상황에 올바른 방향 벡터 반환!
//class TODO

enum e_compare{
  BIG,
  EQUAL,
  SMALL,
};
class myQueue{
  public :
    static const int DATA_SIZE = 1000;
    void  push(t_coordinaete &a);
    // void  pop_back();
    void  pop_front();
    bool  isEmpty();
    t_coordinaete Front();
    t_coordinaete data[DATA_SIZE];//정렬 되어있다는 전제.
    int find(const t_coordinaete &tofind);

  private :
    int front;//데이터 읽으면 늘어나는 인덱스 즉 POP이라고 봐도 됨.
    int rear;//데이터를 푸쉬할 수 있는 공간 인덱스
};
#endif
