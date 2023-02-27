#include<iostream>
using namespace std;
class aaa
{
public:
class bbb
{
public:
void sam()
{
cout<<"Cool"<<endl;
}
};
};
class kkk
{
public:
static int bbb;
};
int kkk::bbb=10;
template<class whatever>
void sam()
{
typename whatever::bbb *k;
}
int main()
{
sam<aaa>();
return 0;
}