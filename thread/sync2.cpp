#include<iostream>
#include<thread>
#include<mutex>
using namespace std;
mutex mutualExclusionObject;
class CommonPlace
{
private:
string data;
public:
void setData(string data)
{
this->data=data;
}
string getData()
{
return this->data;
}
};
CommonPlace commonObject;
void doSomething(string content)
{
lock_guard<mutex> guard(mutualExclusionObject);
commonObject.setData(content);
cout<<commonObject.getData()<<endl;
this_thread::sleep_for(chrono::seconds(1));
cout<<commonObject.getData()<<endl;
}
int main()
{
string a="Hello";
string b="Boys";
string c="Girls";
string d="Welcome";
string e="to";
string f="my";
string g="first";
string h="Presentation";
string i="layer";
thread t1(doSomething,a);
thread t2(doSomething,b);
thread t3(doSomething,c);
thread t4(doSomething,d);
thread t5(doSomething,e);
thread t6(doSomething,f);
thread t7(doSomething,g);
thread t8(doSomething,h);
thread t9(doSomething,i);
t1.join();
t2.join();
t3.join();
t4.join();
t5.join();
t6.join();
t7.join();
t8.join();
t9.join();
return 0;
}