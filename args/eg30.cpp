#include<iostream>
using namespace std;
template<int kkk=10>
void sam(const char * s)
{
for(int e=1;e<=kkk;e++) cout<<s<<endl;
}
int main()
{
sam("Great");
sam<5>("God is great");
sam<3>("Cool");
return 0;
}