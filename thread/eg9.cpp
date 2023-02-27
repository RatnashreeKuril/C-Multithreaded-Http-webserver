#include<iostream>
using namespace std;
class bbb
{
public:
template<class whatever>
bbb(whatever e)
{
cout<<"great"<<endl;
e();
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
cout<<"Operator () got evoked"<<endl;
}

};
int main()
{
aaa a;
bbb b(a);
return 0;
}