#include<iostream>
using namespace std;
void sam(int (*k)(int))
{
int x;
x=10;
int y=x+k(10);
cout<<y<<endl;

}

int main()
{
sam([](int e){return e*e;});
return 0;
}