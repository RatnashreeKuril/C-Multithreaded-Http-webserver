#include<iostream>
using namespace std;
class aaa
{
public:
int doSomething()
{
return 100;
}

};
ostream & operator <<(ostream & o, aaa & kkk)
{
o<<kkk.doSomething();
return o;
}
int main()
{
aaa a;
cout<<a<<endl;
return 0;
}