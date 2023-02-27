#include<windows.h>
#include<stdio.h>
#include<string.h>
int main()
{
int len;
char request[5000];
char response[5000];
WORD ver;
ver=MAKEWORD(1,1);
WSADATA wsaData;
WSAStartup(ver,&wsaData);
int serverSocketDescriptor;
int clientSocketDescriptor;
struct sockaddr_in serverSocketInformation;
struct sockaddr_in clientSocketInformation;
serverSocketDescriptor=socket(AF_INET,SOCK_STREAM,0);
if(serverSocketDescriptor<0)
{
printf("Unable to create server socket\n");
WSACleanup();
return 0;
}
serverSocketInformation.sin_family=AF_INET;
serverSocketInformation.sin_port=htons(5050);
serverSocketInformation.sin_addr.s_addr=htonl(INADDR_ANY);
int successCode=bind(serverSocketDescriptor,(struct sockaddr *)&serverSocketInformation,sizeof(serverSocketInformation));
if(successCode<0)
{
printf("Unable to bind server socket on port %d\n",5050);
closesocket(serverSocketDescriptor);
WSACleanup();
return 0;
}
listen(serverSocketDescriptor,10);
printf("TMServer is ready to accept request on port : %d\n",5050);
len=sizeof(clientSocketInformation);
clientSocketDescriptor=accept(serverSocketDescriptor,(struct sockaddr *)&clientSocketInformation,&len);
if(clientSocketDescriptor<0)
{
printf("Unable to accept client connection\n");
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
strcpy(response,"Welcome to Thinking Machines");
successCode=send(clientSocketDescriptor,response,strlen(response)+1,0);
if(successCode>0)
{
printf("Response sent\n");
}
closesocket(clientSocketDescriptor);
closesocket(serverSocketDescriptor);
WSACleanup();

return 0;
}