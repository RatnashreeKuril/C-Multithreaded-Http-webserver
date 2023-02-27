#include<iostream>
#include<vector>
using namespace std;
template<class ...whatever>
auto getSum(whatever ...n)
{
return (n+...);
}
int main()
{
cout<<getSum(10,20,30,40)<<endl;
cout<<getSum(12,23,34,23,23,435)<<endl;
return 0;
}