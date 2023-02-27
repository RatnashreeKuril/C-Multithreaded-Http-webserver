#include<iostream>
using namespace std;
template<typename ...whatever>
int doSomething(whatever ...n)
{
return printf(std::forward<whatever>(n)...);
}
int main()
{
cout<<doSomething("Cool %d %c %s\n",10,'A',"Great");
return 0;
}
