#include<iostream>
#include<thread>
using namespace std;
class bbb
{
public:
template<class kkk>
bbb(kkk k)
{
k();
}
};
class aaa
{
public:
aaa()
{
cout<<"Default Constructor"<<endl;
}
aaa(const aaa &e)
{
cout<<"Copy constructor"<<endl;
}
void operator()()
{
cout<<"Operator () got called"<<endl;
}
};

int main()
{
aaa a;
bbb b(a);
for(int e=1000;e<=1500;e++);
return 0;
}