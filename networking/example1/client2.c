#include<windows.h>
#include<stdio.h>
#include<string.h>
int main()
{
int id;
char firstName[21];
char lastName[21];
char gender;
char city[21];
char *header=(char*)malloc(sizeof(char*));
id=10035454;
strcpy(firstName,"Amit");
strcpy(lastName,"verma");
strcpy(city,"Mumbai");
gender='M';
char *str=(char*)malloc(sizeof(char*));
sprintf(str,"%d,%s,%s,%c,%s All details are here, (id, name, gender, city)",id,firstName,lastName,gender,city);
printf("%s\n",str);
int len=strlen(str);
sprintf(header,"%-10d",len);
//data entry part over
WSADATA wsaData;
WORD ver;
ver=MAKEWORD(1,1);
int serverSocketDescriptor;
int clientSocketDescriptor;
WSAStartup(ver,&wsaData);
clientSocketDescriptor=socket(AF_INET,SOCK_STREAM,0);
if(clientSocketDescriptor<0)
{
printf("Unable to create socket\n");
return 0;
}
struct sockaddr_in serverSocketInformation;
serverSocketInformation.sin_family=AF_INET;
serverSocketInformation.sin_port=htons(5050);
serverSocketInformation.sin_addr.s_addr=inet_addr("127.0.0.1");
connect(clientSocketDescriptor, (struct sockaddr *)&serverSocketInformation,sizeof(serverSocketInformation));
send(clientSocketDescriptor,header,strlen(header)+1,0);
int successCode=send(clientSocketDescriptor,str,len,0);
if(successCode>0)
{
printf("Data has been sent successfully\n");
}
closesocket(clientSocketDescriptor);
WSACleanup();
return 0;
}