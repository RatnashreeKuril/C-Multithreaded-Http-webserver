#include<iostream>
using namespace std;
void sam(int x)
{
cout<<x<<endl;
}
void sam(char)=delete;
void sam(float)=delete;
void sam(double)=delete;
int main()
{
sam(10);
sam('A');
sam(12.34f);
sam(34.2);
return 0;
}