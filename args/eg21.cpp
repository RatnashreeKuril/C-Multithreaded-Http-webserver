#include<iostream>
#include<tuple>
using namespace std;
int main()
{
tuple<int,char,const char*>t(10,'A',"Great");
cout<<get<0>(t)<<endl;
cout<<get<1>(t)<<endl;
cout<<get<2>(t)<<endl;
return 0;
}