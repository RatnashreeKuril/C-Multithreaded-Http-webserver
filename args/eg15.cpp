#include<iostream>
using namespace std;
auto process(int n1, int n2)
{
return n1-n2;
}
auto process(int n1, int n2, int n3)
{
return n1-n2-n3;
}
auto process(int n1, int n2, int n3, int n4)
{
return n1-n2-n3-n4;
}
int main()
{
cout<<process(10,20)<<endl;
cout<<process(10,20,30)<<endl;
cout<<process(10,20,30,40)<<endl;

return 0;
}