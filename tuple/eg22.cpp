#include<iostream>
using namespace std;
int main()
{
auto a=[](int e){return e*10;};
cout<<a(10)<<endl;
int (*m)(int)=[](int e){return e*10;};
cout<<m(20)<<endl;
int x=m(50);
cout<<x<<endl;

return 0;
}