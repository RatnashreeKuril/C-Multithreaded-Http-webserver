#include<iostream>
#include<thread>
#include<mutex>
using namespace std;
mutex m;
class CommonMedium
{
private:
int num;
public:
CommonMedium()
{
this->num=0;
}
void setNum(int e)
{
this->num=e;
cout<<"Produced : "<<this->num<<endl;
}
int getNum()
{
cout<<"Consumed : "<<this->num<<endl;
return this->num;
}
};
CommonMedium medium;
void producerThread()
{
lock_guard<mutex> guard(m);
for(int e=201;e<=250;e++)
{
medium.setNum(e);

}
}
void consumerThread()
{
lock_guard<mutex> guard(m);
int j;
for(int i=1;i<=50;i++)
{
j=medium.getNum();

}
}
int main()
{
thread t1(producerThread);
thread t2(consumerThread);
t1.join();
t2.join();
return 0;
}