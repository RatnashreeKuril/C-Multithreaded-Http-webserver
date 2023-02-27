#include<iostream>
using namespace std;
template<int k=0,typename aaa>
constexpr int sam(aaa i)
{
if constexpr(k==0)
{
return i*i;
}
else
{
cout<<k<<endl;
sam<k-1>(5);
return i*i*i;
}
}
int main()
{
sam<3>(5);
return 0;
}