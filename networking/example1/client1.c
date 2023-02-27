#include<windows.h>
#include<stdio.h>
#include<string.h>
int main()
{
char request[5000];
char response[5000];
WORD ver;
ver=MAKEWORD(1,1);
WSADATA wsaData;
WSAStartup(ver,&wsaData);
int clientSocketDescriptor;
int serverSocketDescriptor;
struct sockaddr_in serverSocketInformation;
struct sockaddr_in clientSocketInformation;
clientSocketDescriptor=socket(AF_INET,SOCK_STREAM,0);
if(clientSocketDescriptor<0)
{
printf("Unable to create client socket\n");
WSACleanup();
return 0;
}
serverSocketInformation.sin_family=AF_INET;
serverSocketInformation.sin_port=htons(5050);
serverSocketInformation.sin_addr.s_addr=inet_addr("127.0.0.1");
connect(clientSocketDescriptor,(struct sockaddr *)&serverSocketInformation,sizeof(serverSocketInformation));
strcpy(request,"Hi my name is Ratnashree Kuril");
send(clientSocketDescriptor,request,strlen(request)+1,0);
printf("Request sent\n");
recv(clientSocketDescriptor,response,sizeof(response),0);
printf("Response arrived\n");
printf("%s\n",response);
closesocket(clientSocketDescriptor);
WSACleanup();

return 0;
}