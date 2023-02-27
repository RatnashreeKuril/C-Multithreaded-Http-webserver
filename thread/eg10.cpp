#include<iostream>
#include<thread>
using namespace std;
void whatever(int sp,int ep)
{
for(int e=sp;e<ep;e++) cout<<e<<" ";
}

int main()
{
thread t(whatever,10,50);
for(int e=1;e<=9;e++) cout<<e<<" ";
t.join();
return 0;
}