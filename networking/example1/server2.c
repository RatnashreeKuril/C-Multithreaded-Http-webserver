#include<windows.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
WSADATA wsaData;
WORD ver;
int serverSocketDescriptor;
int clientSocketDescriptor;
struct sockaddr_in serverSocketInformation;
struct sockaddr_in clientSocketInformation;
int successCode;
int len;
char *header=(char*)malloc(sizeof(char*));
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
successCode=bind(serverSocketDescriptor ,(struct sockaddr *)&serverSocketInformation ,sizeof(serverSocketInformation));
if(successCode<0)
{
printf("Unable to bind socket to port 5050\n");
WSACleanup();
return 0;
}
listen(serverSocketDescriptor,10);
printf("TMServer is ready to accept request\n");
len=sizeof(clientSocketInformation);
clientSocketDescriptor=accept(serverSocketDescriptor,(struct sockaddr *)&clientSocketInformation,&len);
if(clientSocketDescriptor<0)
{
printf("Unable to accept client connection\n");
closesocket(serverSocketDescriptor);
WSACleanup();
return 0;
}
successCode=recv(clientSocketDescriptor,header,sizeof(header),0);
if(successCode>0)
{
printf("Header recieved \n");
}
int x=0;
int data=0;
while(header[x]!='\0' && header[x]!=' ')
{
data=(header[x]-48)+(data*10);
x++;
}
printf("%d\n",data);
int bytesRecieved=0;
char request[data];
while(bytesRecieved!=data)
{
bytesRecieved=recv(clientSocketDescriptor,request,sizeof(request),0);
}
if(successCode>0)
{
printf("Data recieved\n");
}
printf("%s\n",request);
closesocket(clientSocketDescriptor);
closesocket(serverSocketDescriptor);
WSACleanup();
return 0;
}