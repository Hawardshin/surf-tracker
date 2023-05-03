# include "myQueue.hpp"

myQueue::myQueue(): front(0),rear(0){}
//first 가 second보다
enum e_compare TimeCompare(const myTime& first, const myTime& second){
  if (first.hour != second.hour)
  {
    if (fisrt.hour > second.hour)
      return (BIG);
    return (SMALL);
  }
  if (first.min != second.min)
  {
    if (fisrt.min > second.min)
      return (BIG);
    return (SMALL);
  }
   if (first.sec != second.sec)
  {
    if (fisrt.sec > second.sec)
      return (BIG);
    return (SMALL);
  }
  if (first.csec != second.csec)
  {
    if (fisrt.csec > second.csec)
      return (BIG);
    return (SMALL);
  }
  return (EQUAL);
}
//레런스 가능?
void  myQueue::push(t_coordinaete a){
  data[rear] = a;
  rear = (rear+1)%DATA_SIZE;
  if (isEmpty()){
    Serial.println("IMPOSSIBLE PUSH");
  }
}

t_coordinaete myQueue:: Front(){
  if (isEmpty())
  {
//나중에 예외처리
  }
  return (data[front]);
}
// void  myQueue::pop_back(){
//   if (isEmpty())
//     return;
// }
void  myQueue::pop_front(){
  if (isEmpty())
    return;
  front = (front+1)%DATA_SIZE;
}

bool  myQueue::isEmpty(){
  if (front == rear)
  {
    Serial.println("EMPTY Queue");
    return (true);
  }
}


//시간 변경할 떄 어떻게 해야할까?
//마음에 안들어.. 하 클래스로 바꿀예정
int myQueue::find(const t_coordinaete &tofind){
  bool move_ = 0;
  int bef = -1;
  for (int i=front;i != rear; i= i+1 %DATA_SIZE){
    switch(TimeCompare(tofind.co_time,data[i].co_time))
    {
      //찾아야 하는게 더 크다면
      case SMALL : bef = front;
      front = (front+1) %DATA_SIZE;
            break;
      case EQUAL : return (i);
      case BIG : front = bef;
                return (bef);
    }
  }
  if (i == rear)
    return (-1);
}
