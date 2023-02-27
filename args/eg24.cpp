#include<iostream>
#include<tuple>
using namespace std;
tuple<int, int> addAndSubtract(int e, int f)
{

return {e+f,e-f};
}
int main()
{
int sum,diff;
tie(sum,diff)=addAndSubtract(10,2);
cout<<sum<<endl;
cout<<diff<<endl;

return 0;
}