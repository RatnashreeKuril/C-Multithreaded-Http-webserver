#include<iostream>
#include<stdlib.h>
using namespace std;
class aaa
{
public:
aaa()
{
cout<<"default constructor"<<endl;
}
void * operator new(size_t)=delete;
};
int main()
{
aaa a;
aaa *p;
p=new aaa();
return 0;
}