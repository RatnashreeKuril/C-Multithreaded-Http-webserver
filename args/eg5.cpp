#include<iostream>
using namespace std;
template<typename whatever>
void sam(whatever n)
{
cout<<n<<endl;
}
int main()
{
sam(10);
sam('A');
return 0;
}