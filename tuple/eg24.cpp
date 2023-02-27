#include<iostream>
using namespace std;
class aaa
{
private:
int x;
int y;
public:
void setX(int e)
{
this->x=e;
}
int getX()
{
return this->x;
}

void setY(char m)
{
this->y=m;
}
char getY()
{
return this->y;
}
};

void sortIt(aaa *a, int size, bool (*m) (aaa,aaa))
{
int e,f,oep,iep;
aaa g;
oep=size-2;
iep=size-1;
e=0;
while(e<=oep)
{
f=e+1;
while(f<=iep)
{
if(m(a[f],a[e]))
{
g=a[e];
a[e]=a[f];
a[f]=g;
}
f++;
}
e++;
}



}

int main()
{
aaa a[5];
a[0].setX(10);
a[1].setX(1);
a[2].setX(20);
a[3].setX(3);
a[4].setX(12);

a[0].setY('X');
a[1].setY('I');
a[2].setY('A');
a[3].setY('R');
a[4].setY('Q');

sortIt(a,5, [](aaa left, aaa right){return left.getX()<right.getX();});
for(int e=0;e<=4;e++)
{
cout<<a[e].getX()<<" , "<<a[e].getY()<<endl;
}
cout<<"-----------------------------------"<<endl;
sortIt(a,5, [](aaa left, aaa right){return left.getY()<right.getY();});
for(int e=0;e<=4;e++)
{
cout<<a[e].getX()<<" , "<<a[e].getY()<<endl;
}
return 0;
}