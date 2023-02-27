#include<iostream>
using namespace std;
class aaa
{
private:
int x,y;
public:
aaa()
{
this->x=0;
this->y=0;
}
aaa(int e, int f)
{
this->x=e;
this->y=f;
}
int getX()
{
return this->x;
}
int getY()
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