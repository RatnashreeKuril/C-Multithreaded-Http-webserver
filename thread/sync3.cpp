#include<iostream>
#include<thread>
#include<mutex>
using namespace std;
class CommonMedium
{
private:
int num;
public:
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
for(int e=201;e<=250;e++)
{
medium.setNum(e);
this_thread::sleep_for(chrono::seconds(1));
}
}
void consumerThread()
{
int j;
for(int i=1;i<=50;i++)
{
j=medium.getNum();
this_thread::sleep_for(chrono::seconds(1));
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