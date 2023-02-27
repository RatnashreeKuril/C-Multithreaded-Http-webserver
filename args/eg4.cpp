#include<iostream>
using namespace std;
template<typename ...whatever>
auto getSum(whatever ...n)
{
return (n+...);
}
int main()
{
cout<<"Sum : "<<getSum(10,20,30)<<endl;
cout<<"Sum : "<<getSum(100,200,300,400)<<endl;
return 0;
}