#include<iostream>
#include<tuple>
using namespace std;
template<typename ...whatever>
void sam(whatever ...n)
{
tuple<whatever...>t(n...);
int size=sizeof...(whatever);
cout<<size<<endl;
}

int main()
{
sam(10,20,"Ujjain",'A');
sam(20,20.3f,"Great","Cool",34.2,'Z');


return 0;
}