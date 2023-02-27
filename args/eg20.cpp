#include<iostream>
#include<thread>
using namespace std;

class ThreadManager
{
private:
thread *t;
public:
template<typename ...whatever>
ThreadManager(whatever ...n)
{

}

void start()
{


}




};


void whatever(int sp, int ep)
{
for(int k=sp;k<=ep;k++) cout<<k<<" ";
}

int main()
{
ThreadManager tm(whatever,1,500);
cout<<"Task is about to start on a seperate thread"<<endl<<endl;
tm.start();
for(int j=5001;j<=5150;j++) cout<<j<<" ";
return 0;
}