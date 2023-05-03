#include <iostream>
class myTime{
  public :
    uint8_t hour;
    uint8_t min;
    uint8_t sec;
    uint8_t csec;
    bool operator==(const myTime& obj);
    bool operator!=(const myTime& obj);
    bool operator< (const myTime& obj);
};
bool myTime::operator==(const myTime& obj){
	return (obj.hour== hour && obj.min == min && obj.sec ==sec && obj.csec == csec);
}
bool myTime::operator!=(const myTime& obj){
	return (obj.hour!= hour ||  obj.min != min || obj.sec !=sec || obj.csec != csec);
}

bool myTime::operator>(const myTime& obj){
	return (myTime_value_store > obj.myTime_value_store);
}

bool myTime::operator>=(const myTime& obj){
	return (myTime_value_store >= obj.myTime_value_store);
}

bool myTime::operator<(const myTime& obj){
	return (myTime_value_store < obj.myTime_value_store);
}

bool myTime::operator<=(const myTime& obj){
	return (myTime_value_store <= obj.myTime_value_store);
}

int main(){
  myTime a;
  a.hour =1;
  a.min = 1;
  a.sec = 1;
  a.csec = 1;
  myTime b;
  b.hour =1;
  b.min = 1;
  b.sec = 1;
  b.csec = 1;
  if (a == b)
    std::cout << "SAME\n";
}
