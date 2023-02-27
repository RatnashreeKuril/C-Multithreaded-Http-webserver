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
bool Comparator::operator()(char *left,char *rigth)
{
return strcmp(left,rigth)<0;
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
char * getMIMEType(const char * resource)
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
char isClientSideResource(const char *resource)
{
int i;
for(i=0;resource[i]!='\0' && resource[i]!='.';i++);
if(resource[i]=='\0') return 'N';
return 'Y';
}
Request::Request()
{
this->method=NULL;
this->resource=NULL;
this->mimeType=NULL;
this->isClientSideTechnologyResource='Y';
this->dataCount=0;
this->forwardedResource=NULL;
}
Request::Request(REQUEST *request)
{
this->forwardedResource=NULL;
if(request->method==NULL) this->method=NULL;
else
{
this->method=(char *)malloc((sizeof(char)*strlen(request->method))+1);
strcpy(this->method,request->method);
}
if(request->resource==NULL) this->resource=NULL;
else
{
this->resource=(char *)malloc((sizeof(char)*strlen(request->resource))+1);
strcpy(this->resource,request->resource);
}
if(request->mimeType==NULL) this->mimeType=NULL;
else
{
this->mimeType=(char *)malloc((sizeof(char)*strlen(request->mimeType))+1);
strcpy(this->mimeType,request->mimeType);
}
this->isClientSideTechnologyResource=request->isClientSideTechnologyResource;
if(request->dataCount==0)
{
this->dataCount=0;
}
else
{
this->dataCount=request->dataCount;
int i;
int e;
int j=0;
char *iKey=NULL;
char *iValue=NULL;
Data *d;
if((request->data)!=NULL)
{
while(j<request->dataCount)
{
i=0;e=0;
iKey=NULL;
iValue=NULL;
char *dataReference=request->data[j];
while(dataReference[i]!='\0')
{
while(dataReference[i]!='=')
{
e++;
i++;
}
iKey=(char *)malloc((sizeof(char)*e)+1);
strncpy(iKey,dataReference,e);
iKey[e++]='\0';
e=0;
if(dataReference[i]=='=')
{
i++;
int si=i;
while(dataReference[i]!='\0')
{
i++;e++;
}
iValue=(char *)malloc((sizeof(char )*e)+1);
strncpy(iValue,dataReference+si,e);
iValue[e++]='\0';
}
d=new Data;
d->key=(char *)malloc((sizeof(char)*strlen(iKey))+1);
strcpy(d->key,iKey);
d->value=(char *)malloc((sizeof(char)*strlen(iValue))+1);
strcpy(d->value,iValue);
free(iKey);
free(iValue);
dataMap.insert(pair<char *, Data *>(d->key,d));
}
j++;
}
}
}
}
Request::Data::Data()
{
this->key=NULL;
this->value=NULL;
}
Request::Data::~Data()
{
if(this->key!=NULL) free(this->key);
if(this->value!=NULL) free(this->value);
}

Request::~Request()
{
if(this->method!=NULL) free(this->method);
if(this->resource!=NULL) free(this->resource);
if(this->mimeType!=NULL) free(this->mimeType);
if(this->forwardedResource!=NULL) free(this->forwardedResource);
Data *d;
char *key;
map<char *,Data *, Comparator>::iterator i;
if(!(this->dataMap.empty()))
{
for(i=dataMap.begin();i!=dataMap.end();i++)
{
d=i->second;
delete d;
}
}
dataMap.clear();
}
string Request::getMethod()
{
string method(this->method);
return method;
}
void Request::setResource(char *resource)
{
if(this->resource!=NULL) free(this->resource);
this->resource=(char *)malloc((sizeof(char)*strlen(resource))+1);
strcpy(this->resource,resource);
}
string Request::getResource()
{
string resource(this->resource);
return resource;
}
string Request::getMimeType()
{
string mimeType(this->mimeType);
return mimeType;
}
int Request::getDataCount()
{
return this->dataCount;
}
string Request::get(const char *key)
{
if(key==NULL) return string("");
if(strlen(key)==0) return string("");
map<char *,Data *,Comparator>::iterator i;
char *iKey=(char *)malloc((sizeof(char)*strlen(key))+1);
strcpy(iKey,key);
i=this->dataMap.find(iKey);
if(i==this->dataMap.end()) return string("");
if(i->second==NULL) return string("");
Data *d=i->second;
string value(d->value);
free(iKey);
return value;
}
void Request::forward(const char * resource)
{
if(resource==NULL) return;
if(strlen(resource)==0) return;
if(resource[0]=='/')
{
this->forwardedResource=(char *)malloc(sizeof(char)*strlen(resource));
strcpy(this->forwardedResource,resource+1);
}
else
{
this->forwardedResource=(char *)malloc((sizeof(char)*strlen(resource))+1);
strcpy(this->forwardedResource,resource);
}
}
void Request::setInt(const char * s ,int x)
{
if(s==NULL) return;
if(strlen(s)==0) return;
Data *d=new Data;
char a[11];
sprintf(a,"%d",x);
d->value=(char *)malloc((sizeof(char)*strlen(a))+1);
strcpy(d->value,a);
d->key=(char *)malloc((sizeof(char)*strlen(s))+1);
strcpy(d->key,s);
dataMap.insert(pair<char *, Data *>(d->key,d));
}
int Request::getInt(const char *key)
{
if(key==NULL) return 0;
if(strlen(key)==0) return 0;
map<char *,Data *,Comparator>::iterator i;
Data *d;
char *iKey=(char *)malloc((sizeof(char)*strlen(key))+1);
strcpy(iKey,key);
i=this->dataMap.find(iKey);
if(i==this->dataMap.end()) 
{
return 0;
}
d=i->second;
if(d==NULL) return 0;
free(iKey);
return atoi(d->value);
}
Response::Response(int clientSocketDescriptor, char *mimeType)
{
if(mimeType==NULL) this->mimeType=NULL;
else
{
this->mimeType=(char *)malloc((sizeof(char)*strlen(mimeType))+1);
strcpy(this->mimeType,mimeType);
}
this->clientSocketDescriptor=clientSocketDescriptor;
this->headerSent=0;
}
void Response::write(const string & response)
{
if(this->headerSent==0)
{
char header[500];
sprintf(header,"HTTP/1.1 200 OK\nContent-Type:text/html\nConnection: close\n\n");
send(clientSocketDescriptor,header,strlen(header),0);
this->headerSent=1;
}
if(response.length()==0) return;
send(clientSocketDescriptor,response.c_str(),response.length(),0);
}
void Response::close()
{
closesocket(clientSocketDescriptor);
}
Response::~Response()
{
if(this->mimeType!=NULL) free(mimeType);
}
REQUEST * parseRequest(char *bytes)
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
REQUEST *request=(REQUEST*)malloc(sizeof(REQUEST)); // dynamic memory allocation
printf("Memory allocated for struct REQUEST\n");
request->dataCount=dataCount;
request->data=data;
request->method=(char *)malloc((sizeof(char)*strlen(method))+1); // dynamic memory allocation
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
}
TMWebProjector::~TMWebProjector()
{
printf("Destructor of TMWebProjector class\n");
map<char *,UrlData *>::iterator i;
if(!(dataModel.urlAndPtrOnRequestMap.empty()))
{
for(i=dataModel.urlAndPtrOnRequestMap.begin();i!=dataModel.urlAndPtrOnRequestMap.end();i++)
{
free(i->first);
delete i->second;
dataModel.urlAndPtrOnRequestMap.erase(i);
}
dataModel.urlAndPtrOnRequestMap.clear();
}
printf("Destructor of TMWebProjector class end\n");
}
void TMWebProjector::onRequest(const char *url, void(*ptrOnRequest)(Request &, Response &))
{
if(url==NULL || ptrOnRequest==NULL) return;
UrlData *d=new UrlData;
if(url[0]=='/')
{
d->url=(char *)malloc(sizeof(char)*strlen(url));
strcpy(d->url,url+1);
}
else
{
d->url=(char *)malloc((sizeof(char)*strlen(url))+1);
strcpy(d->url,url);
}
d->ptrOnRequest=ptrOnRequest;
this->dataModel.urlAndPtrOnRequestMap.insert(pair<char *,UrlData *>(d->url,d));
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
REQUEST * request=parseRequest(requestBuffer);
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
if(dataModel.urlAndPtrOnRequestMap.empty())
{
printf("11111111111111\n");
printf("Sending 404 page\n");
char tmp[501];
sprintf(tmp,"<DOCTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>TM Web Projector</title></head><body><h2 style='color:red'>Resource /%s not found</h2></body></html>",request->resource);
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:%d\nConnection: close\n\n",strlen(tmp));
strcat(responseBuffer,tmp);
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
}
else
{
map<char *, UrlData *,Comparator>::iterator i;
i=dataModel.urlAndPtrOnRequestMap.find(request->resource);
if(i==dataModel.urlAndPtrOnRequestMap.end())
{
printf("22222222222222222222\n");
printf("Sending 404 page\n");
char tmp[501];
sprintf(tmp,"<DOCTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>TM Web Projector</title></head><body><h2 style='color:red'>Resource /%s not found</h2></body></html>",request->resource);
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:%d\nConnection: close\n\n",strlen(tmp));
strcat(responseBuffer,tmp);
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
}
else
{
printf("33333333333333333333333\n");
Request rq(request);
// done done
Response rs(clientSocketDescriptor,request->mimeType);
UrlData *d=i->second;
d->ptrOnRequest(rq,rs);
printf("4444444444444444444\n");
if(rq.forwardedResource!=NULL)
{
if(isClientSideResource(rq.forwardedResource)=='Y')
{
int len=strlen(rq.forwardedResource);
int lastIndexOfDot=len-1;
while(lastIndexOfDot>0 && rq.forwardedResource[lastIndexOfDot]!='.') lastIndexOfDot--;
if(extensionEquals(rq.forwardedResource+lastIndexOfDot+1,"sct"))
{
f=fopen(rq.forwardedResource,"r");
if(f==NULL)
{
printf("Sending 404 page\n");
char tmp[501];
sprintf(tmp,"<DOCTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>TM Web Projector</title></head><body><h2 style='color:red'>Resource /%s not found</h2></body></html>",rq.forwardedResource);
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:%d\nConnection: close\n\n",strlen(tmp));
strcat(responseBuffer,tmp);
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
}
else
{
printf("Sending %s\n",rq.forwardedResource);
fseek(f,0,2);
fileLength=ftell(f);
printf("Length of file is : %d\n",fileLength);
fseek(f,0,0);
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:%d\nConnection: close\n\n",fileLength);
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
int i=0;
while(1)
{
fgets(responseBuffer,1024, f);
if(feof(f)) break;
printf("Characters read by fgets : %d\n",strlen(responseBuffer));
printf("%s\n",responseBuffer);
for(int e=0;responseBuffer[e]!='\0';e++)
{
if(responseBuffer[e]=='$')
{
int sp=e;
e+=2;
char a[10];
int f=0;
while(responseBuffer[e]!='}')
{
a[f]=responseBuffer[e];
e++;f++;
}
a[f]='\0';
int value=rq.getInt(a);
sprintf(a,"%d",value);
int tmpLen=strlen(a)+(strlen(responseBuffer)-e);
char tmp[tmpLen];
strcpy(tmp,a);
strcat(tmp,responseBuffer+e+1);
responseBuffer[sp]='\0';
strcat(responseBuffer,tmp);
}
}
send(clientSocketDescriptor, responseBuffer,strlen(responseBuffer), 0);
}
fclose(f);
printf("Characters read by fgets : %d\n",strlen(responseBuffer));
printf("%s\n",responseBuffer);
for(int e=0;responseBuffer[e]!='\0';e++)
{
if(responseBuffer[e]=='$')
{
int sp=e;
e+=2;
char a[10];
int f=0;
while(responseBuffer[e]!='}')
{
a[f]=responseBuffer[e];
e++;f++;
}
a[f]='\0';
int value=rq.getInt(a);
sprintf(a,"%d",value);
int tmpLen=strlen(a)+(strlen(responseBuffer)-e);
char tmp[tmpLen];
strcpy(tmp,a);
strcat(tmp,responseBuffer+e+1);
responseBuffer[sp]='\0';
strcat(responseBuffer,tmp);
}
}
send(clientSocketDescriptor, responseBuffer,strlen(responseBuffer), 0);
closesocket(clientSocketDescriptor);
}
}
else
{
f=fopen(rq.forwardedResource,"rb");
if(f==NULL)
{
printf("Sending 404 page\n");
char tmp[501];
sprintf(tmp,"<DOCTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>TM Web Projector</title></head><body><h2 style='color:red'>Resource /%s not found</h2></body></html>",rq.forwardedResource);
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:%d\nConnection: close\n\n",strlen(tmp));
strcat(responseBuffer,tmp);
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
}
else
{
printf("Sending %s\n",rq.forwardedResource);
fseek(f,0,2);
fileLength=ftell(f);
fseek(f,0,0);
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:%d\nConnection: close\n\n",fileLength);
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
int i=0;
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
}//client side resource if block
}
else
{
if(dataModel.urlAndPtrOnRequestMap.empty())
{
printf("11111111111111\n");
printf("Sending 404 page\n");
char tmp[501];
sprintf(tmp,"<DOCTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>TM Web Projector</title></head><body><h2 style='color:red'>Resource /%s not found</h2></body></html>",rq.forwardedResource);
strcpy(responseBuffer,tmp);
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
}
else
{
map<char *, UrlData *,Comparator>::iterator i;
i=dataModel.urlAndPtrOnRequestMap.find(rq.forwardedResource);
if(i==dataModel.urlAndPtrOnRequestMap.end())
{
printf("22222222222222222222\n");
printf("Sending 404 page\n");
char tmp[501];
sprintf(tmp,"<DOCTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>TM Web Projector</title></head><body><h2 style='color:red'>Resource /%s not found</h2></body></html>",rq.forwardedResource);
strcpy(responseBuffer,tmp);
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
}
else
{
printf("33333333333333333333333\n");
rq.setResource(rq.forwardedResource);
UrlData *d=i->second;
printf("%s\n",d->url);
d->ptrOnRequest(rq,rs);
printf("4444444444444444444\n");
}
}
}// server side resource else block

}


if(request->data!=NULL)
{
for(int i=0;i<request->dataCount;i++) free(request->data[i]);
(request->data);
}
printf("5555555555555555\n");
}
printf("6666666666666666666\n");
}
}
}
}// the infinite loop related to accept method ends here
closesocket(clientSocketDescriptor);
closesocket(serverSocketDescriptor);
WSACleanup();
return;
}