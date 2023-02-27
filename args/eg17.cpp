#include<iostream>
using namespace std;
template<typename ...whatever>
int process(whatever ...n)
{
return (...-n);
}
int main()
{
cout<<process(10,20)<<endl;
cout<<process(10,20,30)<<endl;
cout<<process(10,20,30,40)<<endl;
return 0;
}