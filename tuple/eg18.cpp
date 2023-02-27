#include<iostream>
using namespace std;
int main()
{
auto a=[](){return 10;};
cout<<a()<<endl;
int x=100;
auto b=[x](int e){return e+x;};
cout<<b(50)<<endl;
x=200;
cout<<b(50)<<endl;
return 0;
}