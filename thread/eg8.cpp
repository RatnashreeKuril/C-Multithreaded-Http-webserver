#include<iostream>
using namespace std;
class aaa
{
private:
int x,y;
public:
aaa():x(10),y(20)
{
cout<<"Default constructor"<<endl;
cout<<x<<endl;
cout<<y<<endl;
}
aaa(int e,int f):x(e),y(f)
{
cout<<"Paramaterized constructor"<<endl;
cout<<x<<endl;
cout<<y<<endl;
}
};
int main()
{
aaa a1;
aaa a2(100,200);
return 0;
}