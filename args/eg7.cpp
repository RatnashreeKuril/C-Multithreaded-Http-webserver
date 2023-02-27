#include<iostream>
#include<tuple>
using namespace std;
auto addAndSubtract(int e,int f)
{
return make_tuple(e+f,e-f);
}
int main()
{
auto [sum,diff]=addAndSubtract(10,20);
cout<<sum<<endl;
cout<<diff<<endl;
return 0;
}