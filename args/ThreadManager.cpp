#include<iostream>
#include<thread>
#include<tuple>
#include<array>
#include<vector>
using namespace std;
template<typename ...whatever>
class ThreadManager
{
private:
tuple<whatever...> *t;
thread *p;
public:
ThreadManager(whatever ...n)
{
t=new tuple<whatever...>(n...);
}
~ThreadManager()
{
}

void start()
{

}
};

void something(int sp,int ep)
{
cout<<"something got called"<<endl;
for(int k=sp;k<=ep;k++) cout<<k<<" ";
}
int main()
{
ThreadManager<void(*)(int,int),int,int> tm(something,10,1000);
cout<<"Task is about to start on seperate thread"<<endl<<endl<<endl;
tm.start();
return 0;
}
