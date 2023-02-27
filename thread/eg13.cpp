#include<iostream>
#include<thread>
using namespace std;
void doSomething(int start, int end)
{
for(int e=start;e<=end;e++) cout<<e<<" ";
}
template<typename p2f, typename ...whatever>
class ThreadManager
{
private:
thread *ttt;
p2f funcAdderss;
tuple<whatever ...>t;
public:
ThreadManager(p2f f, whatever ...n):funcAdderss(f),t(n...),ttt(NULL){}
~ThreadManager()
{
if(ttt)
{
ttt->join();
delete(ttt);
}
}
void start()
{
createThread(t,index_sequence_for<whatever...>());
}
template<size_t ...c>
void createThread(tuple<whatever...> &t, index_sequence<c...>)
{
ttt=new thread(funcAdderss,get<c>(t)...);
}
};


int main()
{
ThreadManager<void (*)(int,int),int,int> tm(doSomething,100,200);
cout<<"The task is about to start on a seperate thread"<<endl;
tm.start();
for(int e=1000;e<=1200;e++) cout<<e<<" ";
return 0;
}