#include<iostream>
#include<vector>
using namespace std;
template<class kkk>
kkk getSum(vector<kkk> v)
{
kkk total=0;
typename vector<kkk>::iterator i=v.begin();
while(i!=v.end())
{
total+=*i;
++i;
}
return total;
}
int main()
{
int x[5]={10,20,30,40,50};
int y[3]={100,200,300};
vector<int> v1(x,x+5);
vector<int>v2(y,y+3);
cout<<getSum(v1)<<endl;
cout<<getSum(v2)<<endl;
return 0;
}