#include<iostream>
using namespace std;
template<int kkk=10, typename whatever>
void sam(whatever n)
{
for(int e=1;e<=kkk;e++) cout<<n<<endl;
}
int main()
{
sam<2>(1020);
sam(340.45f);
sam<4>('A');
sam<6>("God is great");
return 0;
}