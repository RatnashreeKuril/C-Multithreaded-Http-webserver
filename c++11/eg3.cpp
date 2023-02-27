#include<iostream>
using namespace std;
class aaa
{
public:
aaa()
{
cout<<"Default constructor"<<endl;
}
aaa(const aaa &)=delete;
aaa & operator=(const aaa&)=delete;
};
int main()
{
aaa a1;
aaa a2(a1);
aaa a3;
a3=a1;
return 0;
}