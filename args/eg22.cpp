#include<iostream>
#include<tuple>
using namespace std;
int main()
{
int x,y,f;
tuple<int,char,float> t(10,'A',10.3f);
tie(x,y,f)=t;
cout<<x<<endl;
cout<<y<<endl;
cout<<f<<endl;

return 0;
}