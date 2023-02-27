#include<iostream>
using namespace std;
void sam(int e)
{
cout<<e<<endl;
}
void sam(char)=delete;
void sam(float)=delete;
void sam(double)=delete;
int main()
{
sam(10);
sam(20.4f);
sam('A');
sam(20.4);
return 0;
}