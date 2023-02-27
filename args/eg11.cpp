#include<iostream>
using namespace std;
class kkk
{
public:
static int x;
};
int kkk::x=0;
int main()
{
cout<<kkk::x<<endl;
return 0;
}