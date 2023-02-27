#include<iostream>
using namespace std;
class aaa
{
private:
int x,y;
public:
constexpr aaa(int e,int f):x(e),y(f){}
constexpr int getX()
{
return x;
}
constexpr int getY()
{
return y;
}
};
int main()
{
aaa a(10,20);
cout<<a.getX()<<endl;
cout<<a.getY()<<endl;
return 0;
}