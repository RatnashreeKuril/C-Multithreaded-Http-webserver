#include<iostream>
using namespace std;
template<int kkk>
void sam(const char * s)
{
for(int e=1;e<=kkk;e++) cout<<s<<endl;
}
int main()
{
sam<5>("God is great");
sam<3>("Cool");
return 0;
}