#include<iostream>
using namespace std;
int main()
{
auto b=[x=50](int e){return e*x;};
cout<<b(2)<<endl;

return 0;
}