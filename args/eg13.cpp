#include<iostream>
using namespace std;
class kkk
{
public:
static int bbb;
};
int kkk::bbb=10;
template<class whatever>
void sam()
{
cout<<whatever::bbb*50;
}
int main()
{
sam<kkk>();
return 0;
}