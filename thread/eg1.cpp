#include<iostream>
#include<thread>
using namespace std;
class bbb
{
public:
template<class kkk>
bbb(kkk e)
{
cout<<"Parametrized constructor of bbb"<<endl;
}
};
class aaa
{
public:
aaa()
{
cout<<"Default constructor"<<endl;
}
aaa(const aaa &a)
{
cout<<"Copy constructor"<<endl;
}
void operator()()
{
for(int j=1000;j<=1500;j++) cout<<j<<" ";
}
};

int main()
{
aaa a;
bbb b(a);
for(int e=100;e<=500;e++) cout<<e<<" ";
return 0;
}