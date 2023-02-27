#include<iostream>
#include<stdlib.h>
using namespace std;
class aaa
{
private:
int x,y;
public:
aaa():x(5),y(50)
{
cout<<"Default constructor"<<endl;
cout<<x<<endl;
cout<<y<<endl;
}
aaa(int e,int f):x(e),y(f)
{
cout<<"Parametarised constructor"<<endl;
cout<<x<<endl;;
cout<<y<<endl;
}
};
int main()
{
aaa a1;
aaa a2(10,20);
return 0;
}
