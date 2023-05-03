# include "myQueue.hpp"
myQueue::myQueue(): begin_idx(0),end_idx(0){}
void  myQueue::push(t_coordinaete &a){
  data[end_idx] = a;
}

bool  myQueue::isfull(){
  if (begin_idx < end_idx && begin_idx + 1 == end_idx)
    return true;
  else if (begin_idx > end_idx && end_idx == 0 && begin_idx)
}
