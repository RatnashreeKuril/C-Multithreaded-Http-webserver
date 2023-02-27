#include<iostream>
using namespace std;
template<int k=0, typename aaa>
constexpr int sam(aaa i)
{
cout<<i<<endl;
cout<<k<<endl;
return i*i*i;
}

int main()
{
sam<3>(0);

return 0;
}