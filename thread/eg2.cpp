#include<iostream>
#include<thread>
using namespace std;
void whatever(int sp, int ep)
{
for(int e=sp;e<=ep;e++) cout<<e<<" ";
}
int main()
{
thread t(whatever,10,500);
for(int j=5001;j<=5600;j++) cout<<j<<" ";
t.join();
return 0;
}