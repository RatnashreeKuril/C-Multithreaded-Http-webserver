#include<iostream>
#include<tuple>
using namespace std;
template<typename ...whatever>
ostream & operator<<(ostream &o, tuple<whatever...> & k)
{
o<<get<0>(k)<<endl;
o<<get<1>(k)<<endl;
o<<get<2>(k)<<endl;
o<<get<3>(k)<<endl;
o<<get<4>(k)<<endl;
return o;
}

int main()
{
tuple<int,int,int,int,int> t(10,20,30,40,50);
cout<<t<<endl;
return 0;
}