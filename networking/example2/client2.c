#include<windows.h>
#include<stdio.h>
#include<string.h>
int main()
{
char *request=(char*)malloc(sizeof(char*));
char response[5000];
WORD ver;
WSADATA wsaData;
int clientSocketDescriptor;
int successCode;
struct sockaddr_in serverSocketInformation;
ver=MAKEWORD(1,1);
WSAStartup(ver,&wsaData);
clientSocketDescriptor=socket(AF_INET,SOCK_STREAM,0);
if(clientSocketDescriptor<0)
{
printf("Unable to create socket\n");
return 0;
}
serverSocketInformation.sin_family=AF_INET;
serverSocketInformation.sin_port=htons(5050);
serverSocketInformation.sin_addr.s_addr=inet_addr("127.0.0.1");
connect(clientSocketDescriptor,(struct sockaddr *)&serverSocketInformation,sizeof(serverSocketInformation));
strcpy(request,"e are ready to accept request\nRequest arrived\nHello my name is Ratnashree kuril.\nResponse sent");
send(clientSocketDescriptor,request,strlen(request)+1,0);
recv(clientSocketDescriptor,response,sizeof(response),0);
printf("%s\n",response);
closesocket(clientSocketDescriptor);
WSACleanup();
return 0;
}