#include<iostream>
#include<vector>
using namespace std;
template<class whatever>
whatever getSum(vector<whatever> collection)
{
typename vector<whatever>::iterator i=collection.begin();
whatever total=0;
while(i!=collection.end())
{
total+=(*i);
++i;
}
return total;
}


int main()
{
int x[3]={20,30,40};
int y[5]={100,200,300,400,500};
vector<int> v1(x,x+3);
vector<int> v2(y,y+5);
cout<<"Sum : "<<getSum(v1)<<endl;
cout<<"Sum : "<<getSum(v2)<<endl;
return 0;
}