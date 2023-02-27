#include<tmwp>
#include<iostream>
using namespace std;
using namespace tmwp;
/*void doSomething(int dataCount, char *data[])
{
cout<<"great, this code got executed on server side"<<endl;
if(dataCount>0) cout<<"Data that arrived"<<endl;
for(int i=0;i<dataCount;i++)
{
cout<<data[i]<<endl;
}
}*/

void doSomething(Request &request, Response &response)
{
string n=request.get("nm");
cout<<"nm : "<<n<<endl;
string c=request.get("ct");
cout<<"ct : "<<c<<endl;
response.write("<!DOCTYPE HTML>");
response.write("<HTML lang='en'>");
response.write("<head>");
response.write("<title>whatever</title>");
response.write("<meta charset='utf-8'>");
response.write("</head>");
response.write("<body>");
response.write("Hello ");
response.write(n);
response.write("<BR>");
response.write("Data saved");
response.write("</body>");
response.write("</html>");
response.close();
}
int main()
{
TMWebProjector server(8080);
server.onRequest("/register",doSomething);
server.start();
return 0;
}