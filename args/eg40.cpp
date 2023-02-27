#include<iostream>
using namespace std;
template<int k=0, typename aaaa>
constexpr int sam(aaaa i)
{
cout<<i<<endl;
cout<<k<<endl;
return i*i*i;
}
int main()
{
cout<<sam<3>(10);
return 0;
}