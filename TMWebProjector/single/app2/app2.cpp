#include<iostream>
#include<tmwp>
using namespace tmwp;
using namespace std;
void one(Request &request, Response &response)
{
cout<<"One got called"<<endl;
request.forward("/xyz.html");
}
void two(Request &request, Response &response)
{
cout<<"Two got called"<<endl;
request.setInt("abcd",23);
request.setInt("pqr",33);
request.setInt("lmn",96);
request.forward("/three");
}
void three(Request &request, Response &response)
{
cout<<"Three got called"<<endl;
int x=request.getInt("abcd");
cout<<x<<endl;
x=request.getInt("pqr");
cout<<x<<endl;
x=request.getInt("lmn");
cout<<x<<endl;
response.write("<!DOCTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>Whatever</title></head><body><h1>Cool</h1></body></html>");
response.close();
}
int main()
{
TMWebProjector server(7070);
server.onRequest("/one",one);
server.onRequest("/two",two);
server.onRequest("/three",three);
server.start();
return 0;
}