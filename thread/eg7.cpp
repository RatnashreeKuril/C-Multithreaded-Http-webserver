#include<iostream>
using namespace std;
template<class cartoon>
class aaa
{
private:
cartoon x;
public:
aaa(cartoon k)
{
cout<<"Paramaterized constructor"<<endl;
this->x=k;
cout<<x;
}
aaa(char)=delete;
};
int main()
{
aaa<int> a(12);
aaa<char> a1('A');
return 0;
}