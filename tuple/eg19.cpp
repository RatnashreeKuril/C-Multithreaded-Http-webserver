#include<iostream>
using namespace std;
int main()
{
int x=100;
auto b=[x](int e){x=x+10; return e+x;};
cout<<b(50)<<endl;

return 0;
}