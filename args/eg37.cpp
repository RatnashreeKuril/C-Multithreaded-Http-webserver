#include<iostream>
using namespace std;
class aaa
{
private:
int x,y;
public:
constexpr aaa():x(0),y(0) {}
constexpr aaa(int e, int f):x(e),y(f) {}
constexpr int getX()
{
return this->x;
}
constexpr int getY()
{
return this->y;
}
};

int main()
{
aaa w(10,20);
cout<<w.getX()<<endl;
cout<<w.getY()<<endl;
return 0;
}