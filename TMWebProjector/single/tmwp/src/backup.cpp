#include<iostream>
#include<urlencoder>
#include<tmwp>
#include<windows.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<map>
using namespace tmwp;
using namespace std;
Response::Response(int clientSocketDescriptor)
{
this->clientSocketDescriptor=clientSocketDescriptor;
this->isClosed=false;
this->headerCreated=false;
}
string Request::get(const char *key)
{
if(key==null) return " ";
if(strlen(key)==0) return " ";

}
void Response::createHeader()
{
char header[51];
strcpy(header,"HTTP/1.1 200 OK\nContent-Type:text/html\n\n");
send(clientSocketDescriptor,header,strlen(header),0);
this->headerCreated=true;
}
void Response::write(const char *str)
{
if(str==NULL) return;
int len=strlen(str);
if(len==0) return;
if(!this->headerCreated) createHeader();
send(clientSocketDescriptor,str,len,0);
}
void Response::close()
{
if(this->isClosed) return;
closesocket(clientSocketDescriptor);
this->isClosed=true;
}



int extensionEquals(const char *left ,const char *rigth)
{
char a,b;
while(*left && *rigth)
{
a=*left;
b=*rigth;
if(a>=65 && a<=90) a+=32;
if(b>=65 && b<=90) b+=32;
if(a!=b) return 0;
left++;
rigth++;
}
return *left==*rigth;
}
char * getMIMEType(char * resource)
{
char *mimeType;
mimeType=NULL;
int len=strlen(resource);
if(len<4) return mimeType;
int lastIndexOfDot=len-1;
while(lastIndexOfDot>0 && resource[lastIndexOfDot]!='.') lastIndexOfDot--;
if(lastIndexOfDot==0) return mimeType;
if(extensionEquals(resource+lastIndexOfDot+1,"html"))
{
mimeType=(char*)malloc(sizeof(char)*10); // dynamic memory allocation
strcpy(mimeType,"text/html");
}
if(extensionEquals(resource+lastIndexOfDot+1,"css"))
{
mimeType=(char*)malloc(sizeof(char)*9); // dynamic memory allocation
strcpy(mimeType,"text/css");
}
if(extensionEquals(resource+lastIndexOfDot+1,"js"))
{
mimeType=(char*)malloc(sizeof(char)*16); // dynamic memory allocation
strcpy(mimeType,"text/javascript");
}
if(extensionEquals(resource+lastIndexOfDot+1,"jpeg"))
{
mimeType=(char*)malloc(sizeof(char)*11); // dynamic memory allocation
strcpy(mimeType,"image/jpeg");
}
if(extensionEquals(resource+lastIndexOfDot+1,"jpg"))
{
mimeType=(char*)malloc(sizeof(char)*11); // dynamic memory allocation
strcpy(mimeType,"image/jpeg");
}
if(extensionEquals(resource+lastIndexOfDot+1,"png"))
{
mimeType=(char*)malloc(sizeof(char)*10); // dynamic memory allocation
strcpy(mimeType,"image/png");
}
if(extensionEquals(resource+lastIndexOfDot+1,"ico"))
{
mimeType=(char*)malloc(sizeof(char)*13); // dynamic memory allocation
strcpy(mimeType,"image/x-icon");
}
return mimeType;
}
char isClientSideResource(char *resource)
{
int i;
for(i=0;resource[i]!='\0' && resource[i]!='.';i++);
if(resource[i]=='\0') return 'N';
return 'Y';
}
Request * parseRequest(char *bytes)
{

char method[11];
char resource[1001];
int i,j;
for(i=0;bytes[i]!=' ';i++)
{
method[i]=bytes[i];
}
method[i]='\0';
i+=2;
char **data=NULL;
int dataCount=0;
if(strcmp(method,"GET")==0)
{
// whatever?kknfjsf=njjknjns+cj&mnjjgjhj=hjnhjcbh&mkejjcbh=jhkjl
for(j=0;bytes[i]!=' ';j++,i++)
{
if(bytes[i]=='?') break;
resource[j]=bytes[i];
}
resource[j]='\0';
if(bytes[i]=='?')
{
char *query=URLEncoder::decoder(bytes+(i+1));
i=0 ;
int si=i;
dataCount=0;
while(query[i]!='\0')
{
if(query[i]=='&') dataCount++;
i++;
}
dataCount++;
data=(char**)malloc(sizeof(char *)*dataCount);
int *pc=(int *)malloc(sizeof(int)*dataCount);
i=si;
int j=0;
while(query[i]!='\0')
{
if(query[i]=='&')
{
pc[j]=i;
j++;
}
i++;
}
pc[j]=i;
i=si;
j=0;
int howManyToPick;
while(j<dataCount)
{
howManyToPick=pc[j]-i;
data[j]=(char *)malloc(sizeof(char)*(howManyToPick+1));
strncpy(data[j],query+i,howManyToPick);
data[j][howManyToPick]='\0';
i=pc[j]+1;
j++;
}
}
}// method is of GET type
printf("Request arrived for %s\n",resource);
Request *request=(Request*)malloc(sizeof(Request)); 
printf("Memory allocated for struct Request\n");
request->dataCount=dataCount;
request->data=data;
request->method=(char *)malloc((sizeof(char)*strlen(method))+1);
strcpy(request->method,method);
if(resource[0]=='\0')
{
request->resource=NULL;
request->isClientSideTechnologyResource='Y';
request->mimeType=NULL;
}
else
{
request->resource=(char *)malloc((sizeof(char)*strlen(resource))+1); // dynamic memory allocation
strcpy(request->resource,resource);
request->isClientSideTechnologyResource=isClientSideResource(resource);
request->mimeType=getMIMEType(resource);
}
return request;
}
TMWebProjector::TMWebProjector(int portNumber)
{
this->portNumber=portNumber;
this->url=NULL;
this->ptrOnRequest=NULL;
}
TMWebProjector::~TMWebProjector()
{
if(this->url) delete [] this->url;
}

void TMWebProjector::onRequest(const char *url, void(*ptrOnRequest)(Request &, Response &))
{
if(this->url) delete [] this->url;
this->url=NULL;
this->ptrOnRequest=NULL;
if(url==NULL || ptrOnRequest==NULL) return;
this->url=new char[strlen(url)+1];
strcpy(this->url,url);
this->ptrOnRequest=ptrOnRequest;
}
void TMWebProjector::start()
{
char g;
int i,rc;
FILE *f;
char message[101];
int fileLength;
char requestBuffer[8192]; // 8192 1024 * 8
char responseBuffer[1024]; // A chunk of 1024
int bytesExtracted;
WSADATA wsaData;
WORD ver;
int serverSocketDescriptor;
int clientSocketDescriptor;
struct sockaddr_in serverSocketInformation;
struct sockaddr_in clientSocketInformation;
int successCode;
int len;
ver=MAKEWORD(1,1);
WSAStartup(ver,&wsaData);
serverSocketDescriptor=socket(AF_INET,SOCK_STREAM,0);
if(serverSocketDescriptor<0)
{
printf("Unable to create socket\n");
return;
}
serverSocketInformation.sin_family=AF_INET;
serverSocketInformation.sin_port=htons(this->portNumber);
serverSocketInformation.sin_addr.s_addr=htonl(INADDR_ANY);
successCode=bind(serverSocketDescriptor,(struct sockaddr*)&serverSocketInformation, sizeof(serverSocketInformation));
if(successCode<0)
{
sprintf(message,"Unable to bind server socket to port %d\n",this->portNumber);
printf("%s\n",message);
WSACleanup();
return;
}
listen(serverSocketDescriptor,10);
len=sizeof(clientSocketInformation);
while(1)
{
sprintf(message,"TMServer is ready to accept request on port %d\n",this->portNumber);
printf("%s\n",message);
clientSocketDescriptor=accept(serverSocketDescriptor,(struct sockaddr*)&clientSocketInformation,&len);
if(clientSocketDescriptor<0)
{
printf("Unable to connect to client connection\n");
closesocket(serverSocketDescriptor);
WSACleanup();
return;
}
bytesExtracted=recv(clientSocketDescriptor,requestBuffer,sizeof(requestBuffer),0);
if(bytesExtracted<0)
{
// yet to be decided
}
else 
if(bytesExtracted==0)
{
// yet to be decided
}
else
{
requestBuffer[bytesExtracted]='\0';
printf("%s\n",requestBuffer);
Request * request=parseRequest(requestBuffer);
if(request->isClientSideTechnologyResource=='Y')
{
if(request->resource==NULL)
{
f=fopen("index.html","rb");
if(f!=NULL) printf("Sending index.html\n");
if(f==NULL)
{
f=fopen("index.htm","rb");
if(f!=NULL) printf("Sending index.htm\n");
if(f==NULL)
{
strcpy(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:163\nConnection: close\n\n<DOCTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>TM Web Projector</title></head><body><h2 style='color:red'>Resource / not found</h2></body></html>");
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
}
else
{
fseek(f,0,2);
fileLength=ftell(f);
fseek(f,0,0);
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:%d\nConnection: close\n\n",fileLength);
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
i=0;
while(i<fileLength)
{
rc=fileLength-i;
if(rc>1024) rc=1024;
fread(&responseBuffer, rc, 1, f);
send(clientSocketDescriptor, responseBuffer, rc, 0);
i+=rc;
}
fclose(f);
closesocket(clientSocketDescriptor);
}
}
else
{
fseek(f,0,2);
fileLength=ftell(f);
fseek(f,0,0);
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:%s\nContent-Length:%d\nConnection: close\n\n",request->mimeType,fileLength);
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
i=0;
while(i<fileLength)
{
rc=fileLength-i;
if(rc>1024) rc=1024;
fread(&responseBuffer, rc, 1, f);
send(clientSocketDescriptor, responseBuffer, rc, 0);
i+=rc;
}
fclose(f);
closesocket(clientSocketDescriptor);
}
}
else
{
// resource name is present
f=fopen(request->resource,"rb");
if(f!=NULL) printf("Sending %s\n",request->resource);
if(f==NULL)
{
printf("Sending 404 page\n");
char tmp[501];
sprintf(tmp,"<DOCTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>TM Web Projector</title></head><body><h2 style='color:red'>Resource /%s not found</h2></body></html>",request->resource);
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:%d\nConnection: close\n\n",strlen(tmp));
strcat(responseBuffer,tmp);
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
}
else
{
fseek(f,0,2);
fileLength=ftell(f);
fseek(f,0,0);
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:%s\nContent-Length:%d\nConnection: close\n\n",request->mimeType,fileLength);
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
i=0;
while(i<fileLength)
{
rc=fileLength-i;
if(rc>1024) rc=1024;
fread(&responseBuffer, rc, 1, f);
send(clientSocketDescriptor, responseBuffer, rc, 0);
i+=rc;
}
fclose(f);
closesocket(clientSocketDescriptor);
}
}
}
else
{
// what to do in case of server side resource, is yet to be decided

if(this->url==NULL || this->ptrOnRequest==NULL)
{

printf("Sending 404 page\n");
char tmp[501];
sprintf(tmp,"<DOCTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>TM Web Projector</title></head><body><h2 style='color:red'>Resource /%s not found</h2></body></html>",request->resource);
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:%d\nConnection: close\n\n",strlen(tmp));
strcat(responseBuffer,tmp);
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
}
else
{
int ii=0;
if(this->url[0]=='/') ii=1;
if(strcmp(this->url+ii,request->resource)==0)
{
Response rs(clientSocketDescriptor);
this->ptrOnRequest(*request,rs);
if(request->data!=NULL)
{
for(int i=0;i<request->dataCount;i++) free(request->data[i]);
(request->data);
}
/*
printf("Sending processed page\n");
char tmp[501];
sprintf(tmp,"<DOCTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>TM Web Projector</title></head><body><h2 style='color:red'>Resource /%s processed</h2></body></html>",request->resource);
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:%d\nConnection: close\n\n",strlen(tmp));
strcat(responseBuffer,tmp);
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
*/
}
else
{
printf("Sending 404 page\n");
char tmp[501];
sprintf(tmp,"<DOCTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>TM Web Projector</title></head><body><h2 style='color:red'>Resource /%s not found</h2></body></html>",request->resource);
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:%d\nConnection: close\n\n",strlen(tmp));
strcat(responseBuffer,tmp);
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
}
}
}
}
}// the infinite loop related to accept method ends here
closesocket(clientSocketDescriptor);
closesocket(serverSocketDescriptor);
WSACleanup();
return;
}