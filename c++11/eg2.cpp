#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main()
{
vector<int> v{30,20,30,10,30,20,40,50,20,60};
cout<<count(v.begin(),v.end(),20);

return 0;
}