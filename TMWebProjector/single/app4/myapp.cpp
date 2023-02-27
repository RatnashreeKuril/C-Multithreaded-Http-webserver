#include "tpl.h"
#include<tmwp>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<fstream>
#include<ctime>
using namespace std;
using namespace tmwp;
void dispatchTime(Request &request, Response &response)
{
time_t t=time(0);
char *now=ctime(&t);
response.write("<!DOCTYPE HTML>");
response.write("<html lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>The Clock</title>");
response.write("</head>");
response.write("<body>");
response.write("<h1>");
response.write(now);
response.write("</h1>");
response.write("<a href='now'>Refresh</a><br>");
response.write("<a href='index.html'>Home</a><br>");
response.write("</body>");
response.write("</html>");
response.close();
}
void getCityView(Request & request, Response & response)
{
cout<<"getCityView is being processed"<<endl;
string cityCodeString=request.get("cityCode");
cout<<"("<<cityCodeString<<")"<<endl;
int cityCode=atoi(cityCodeString.c_str());
cout<<cityCode<<endl;
if(cityCode==1) request.forward("Ujjain.html");
else if(cityCode==2) request.forward("Indore.html");
else if(cityCode==3) request.forward("Dewas.html");
else 
{
request.setKeyValue("error","Invalid choice, City not selected");
request.forward("abcd.tpl");
}
}
void saveEnquiry(Request & request, Response & response)
{
string n=request.getValue("nm");
string c=request.getValue("ct");
string a=request.getValue("ad");
string m=request.getValue("msg");
cout<<"Data recived"<<endl;
cout<<"Name : "<<n<<endl;
cout<<"City : "<<c<<endl;
cout<<"Address : "<<a<<endl;
cout<<"Query : "<<m<<endl;
request.forward("saveNotification.html");
}
int main()
{
TMWebProjector server(8080);
server.onRequest("/now",dispatchTime);
server.onRequest("/getCity",getCityView);
server.onRequest("/addEnquiry",saveEnquiry);
registerTPLs(&server);
server.start();
return 0;
}