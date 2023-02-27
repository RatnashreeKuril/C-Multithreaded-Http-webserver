#include<iostream>
#include<urlencoder>
#include<tmwp>
#include<windows.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<map>
#include<thread>
using namespace tmwp;
using namespace std;
void Request::setKeyValue(string k, string v)
{
if(k.length()==0) return;
keyValues.insert(pair<string, string>(k,v));
}
string Request::getValue(string k)
{
map<string, string>::iterator i;
i=keyValues.find(k);
if(i==keyValues.end()) return string("");
return i->second;
}
string Request::get(string name)
{
string val;
int i,e;
for(i=0;i<this->dataCount;i++)
{
for(e=0;data[i][e]!='\0' && data[i][e]!='=';e++);
if(data[i][e]!='=') continue; //back to next cycle of for loop
if(strncmp(data[i],name.c_str(),e)==0) break;
}
if(i==this->dataCount)
{
val=" ";
}
else
{
val=string(data[i]+(e+1));
}
return val;
}
void Request::forward(string forwardTo)
{
this->forwardTo=forwardTo;
}
Response::Response(int clientSocketDescriptor)
{
this->clientSocketDescriptor=clientSocketDescriptor;
this->isClosed=false;
this->headerCreated=false;
}
void Response::createHeader()
{
char header[51];
strcpy(header,"HTTP/1.1 200 OK\nContent-Type:text/html\n\n");
send(clientSocketDescriptor,header,strlen(header),0);
this->headerCreated=true;
}
void Response::write(string str)
{
this->write(str.c_str());
}
void Response::write(string & str)
{
this->write(str.c_str());
}
void Response::write(const char *str)
{
if(str==NULL) return;
int len=strlen(str);
if(len==0) return;
if(!this->headerCreated) createHeader();
printf("%s\n",str);
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
mimeType=(char*)malloc(sizeof(char)*10);
strcpy(mimeType,"text/html");
}
if(extensionEquals(resource+lastIndexOfDot+1,"tpl"))
{
mimeType=(char*)malloc(sizeof(char)*10);
strcpy(mimeType,"text/html");
}
if(extensionEquals(resource+lastIndexOfDot+1,"css"))
{
mimeType=(char*)malloc(sizeof(char)*9);
strcpy(mimeType,"text/css");
}
if(extensionEquals(resource+lastIndexOfDot+1,"js"))
{
mimeType=(char*)malloc(sizeof(char)*16);
strcpy(mimeType,"text/javascript");
}
if(extensionEquals(resource+lastIndexOfDot+1,"jpeg"))
{
mimeType=(char*)malloc(sizeof(char)*11);
strcpy(mimeType,"image/jpeg");
}
if(extensionEquals(resource+lastIndexOfDot+1,"jpg"))
{
mimeType=(char*)malloc(sizeof(char)*11);
strcpy(mimeType,"image/jpeg");
}
if(extensionEquals(resource+lastIndexOfDot+1,"png"))
{
mimeType=(char*)malloc(sizeof(char)*10);
strcpy(mimeType,"image/png");
}
if(extensionEquals(resource+lastIndexOfDot+1,"ico"))
{
mimeType=(char*)malloc(sizeof(char)*13);
strcpy(mimeType,"image/x-icon");
}
return mimeType;
}
char isClientSideResource(char *resource)
{
int i;
for(i=0;resource[i]!='\0' && resource[i]!='.';i++);
if(strcmp(resource+i,".tpl")==0) return 'N';
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
//Request *request=(Request*)malloc(sizeof(Request)); 
Request *request=new Request;
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
void TMWebProjector::operator()(int clientSocketDescriptor)
{
int bytesExtracted;
char requestBuffer[8192]; // 8192 1024 * 8
char responseBuffer[1024]; // A chunk of 1024
FILE *f;
int fileLength,i,rc;
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
while(1) // infinite loop to enable the forwarding feature
{
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
break;
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
break;
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
break;
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
break;
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
break;
}
}
}
else
{
printf("000000000000000000\n");
// what to do in case of server side resource, is yet to be decided
map<string, void (*)(Request &, Response &)>::iterator iter;
iter=requestMappings.find(string("/")+string(request->resource));
printf("11111111111111111111111111111111111\n");
if(iter==requestMappings.end())
{
printf("222222222222222222222222222222222222\n");
printf("Sending 404 page\n");
char tmp[501];
sprintf(tmp,"<DOCTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>TM Web Projector</title></head><body><h2 style='color:red'>Resource /%s not found</h2></body></html>",request->resource);
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:%d\nConnection: close\n\n",strlen(tmp));
strcat(responseBuffer,tmp);
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
break;
}
else
{
printf("3333333333333333333333333333333\n");
Response response(clientSocketDescriptor);
iter->second(*request,response);
if(request->forwardTo.length()>0)
{
free(request->resource);
request->resource=(char *)malloc((sizeof(char)*request->forwardTo.length())+1); // dynamic memory allocation
strcpy(request->resource,request->forwardTo.c_str());
request->isClientSideTechnologyResource=isClientSideResource(request->resource);
request->mimeType=getMIMEType(request->resource);
request->forwardTo.clear();
printf("4444444444444444444444444444\n");
continue;
}
printf("555555555555555555555555555555555555555\n");
if(request->data!=NULL)
{
for(int i=0;i<request->dataCount;i++) free(request->data[i]);
free(request->data);
}
printf("66666666666666666666666666666666666666666\n");
break;
}
}

} // the infinite loop introduced because of the forwarding feature ends here

}
}
TMWebProjector::TMWebProjector(int portNumber)
{
this->portNumber=portNumber;
this->requestMappings.insert(pair<string,void (*) (Request &, Response &)>"shutdown",TMWebProjector::TMShutdown));
}
TMWebProjector::TMWebProjector(const TMWebProjector & other)
{
this->portNumber=other.portNumber;
this->requestMappings=other.requestMappings;
}
TMWebProjector::~TMWebProjector()
{
}

void TMWebProjector::onRequest(string url, void(*ptrOnRequest)(Request &, Response &))
{
if(url.length()==0 || ptrOnRequest==NULL) return;
this->requestMappings.insert(pair<string ,void (*)(Request &, Response &)>(url,ptrOnRequest));
}
void TMWebProjector::close()
{

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
successCode=bind(serverSocketDescriptor,(struct sockaddr*)&serverSocketInformation, (unsigned int)sizeof(serverSocketInformation));
if(successCode<0)
{
sprintf(message,"Unable to bind server socket to port %d\n",this->portNumber);
printf("%s\n",message);
WSACleanup();
return;
}
listen(serverSocketDescriptor,10);
len=sizeof(clientSocketInformation);
while(1) // loop to accept connection
{
sprintf(message,"TMServer is ready to accept request on port %d\n",this->portNumber);
printf("%s\n",message);
clientSocketDescriptor=accept(serverSocketDescriptor,(struct sockaddr*)&clientSocketInformation,&len);
if(clientSocketDescriptor<0)
{
printf("Unable to connect to client connection\n");
closesocket(clientSocketDescriptor);
WSACleanup();
return;
}
thread *t=new thread(*this,clientSocketDescriptor);
} // the infinite loop related to accept method ends here
closesocket(clientSocketDescriptor);
closesocket(serverSocketDescriptor);
WSACleanup();
return;
}