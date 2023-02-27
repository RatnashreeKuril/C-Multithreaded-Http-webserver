#include<windows.h>
#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;
void Response(int clientSocketDescriptor, string mimeType)
{
char header[500];
sprintf(header,"HTTP/1.1 200 OK\nContent-Type:%s\nConnection: close\n\n",mimeType.c_str());
send(clientSocketDescriptor,header,strlen(header),0);
}
void write(int clientSocketDescriptor, string response)
{
if(response.length()==0) return;
send(clientSocketDescriptor,response.c_str(),response.length(),0);
}

int main()
{
char request[5000];
char response[5000];
int successCode;
int len;
WSADATA wsaData;
WORD ver; 
int serverSocketDescriptor;
int clientSocketDescriptor;
struct sockaddr_in serverSocketInformation;
struct sockaddr_in clientSocketInformation;
ver=MAKEWORD(1,1);
WSAStartup(ver,&wsaData);
serverSocketDescriptor=socket(AF_INET,SOCK_STREAM,0);
if(serverSocketDescriptor<0)
{
printf("Unable to create socket\n");
return 0;
}
serverSocketInformation.sin_family=AF_INET;
serverSocketInformation.sin_port=htons(5050);
serverSocketInformation.sin_addr.s_addr=htonl(INADDR_ANY);
successCode=bind(serverSocketDescriptor,(struct sockaddr *)&serverSocketInformation,sizeof(serverSocketInformation));
if(successCode<0)
{
printf("Unable to bind server socket to port 5050\n");
WSACleanup();
return 0;
}
listen(serverSocketDescriptor,10);
printf("TM server is ready to accept request\n");
len=sizeof(clientSocketInformation);
clientSocketDescriptor=accept(serverSocketDescriptor,(struct sockaddr *)&clientSocketInformation,&len);
if(clientSocketDescriptor<0)
{
printf("Unable to connect to client connection\n");
closesocket(serverSocketDescriptor);
WSACleanup();
return 0;
}
successCode=recv(clientSocketDescriptor,request,sizeof(request),0);
if(successCode>0)
{
printf("Request arrived\n");
printf("%s\n",request);
}
char header[101];
int f=0;
int e=5;
string RollNo=new string[5];
RollNo={"101","102","104","105"};
string i=new string[5];
i={"1","2","3","4","5"};
Response(clientSocketDescriptor,"text/html");
write(clientSocketDescriptor, "<!DOCTYPE HTML>");
write(clientSocketDescriptor,"<html lang='en'>");
write(clientSocketDescriptor,"<head>");
write(clientSocketDescriptor,"<meta charset='utf-8'>");
write(clientSocketDescriptor,"<title>whatever</title>");
write(clientSocketDescriptor,"</head>");
write(clientSocketDescriptor,"<body>");
write(clientSocketDescriptor,"<h1>Welcome to Thinking Machines</h1>");
write(clientSocketDescriptor,"<Table border='1'>");
write(clientSocketDescriptor,"<TR><TD>S.No.</td><td>Roll No.</td><td>class</td></TR>");
while(f<e)
{
write(clientSocketDescriptor,"<tr><td>");

write(clientSocketDescriptor,"1");
write(clientSocketDescriptor,"</td><td>");
write(clientSocketDescriptor,string(RollNo));
write(clientSocketDescriptor,"</td><td>");
write(clientSocketDescriptor,"class I</td><tr>");
f++;
}
write(clientSocketDescriptor,"</table>");
write(clientSocketDescriptor,"</body>");
write(clientSocketDescriptor,"</html>");
if(successCode>0)
{
printf("Response sent\n");
}
else
{
printf("Unable to send response\n");
}
closesocket(clientSocketDescriptor);
closesocket(serverSocketDescriptor);
WSACleanup();
return 0;
}