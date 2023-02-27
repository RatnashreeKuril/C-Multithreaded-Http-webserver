#include<iostream>
using namespace std;
template<int k=0, typename aaa>
constexpr void sam(aaa i)
{
cout<<i<<endl;
cout<<k<<endl;

}

int main()
{
sam<3>(0);

return 0;
}