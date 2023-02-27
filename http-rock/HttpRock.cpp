#include<stdio.h>
#include<string.h>
#include<iostream>
#include<windows.h>
#include<map>
#include<vector>
#include<thread>
#include<mutex>
#include<tuple>
using namespace std;
mutex mutualExclusionObject;
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
char * getMimeType(const char *resource)
{
char * mimeType;
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
return mimeType;
}
class Request
{

};
class Response
{
string message;
string contentType;
int clientSocketDescriptor;
bool messageSent;
public:
Response(int clientSocketDescriptor)
{
this->clientSocketDescriptor=clientSocketDescriptor;
this->messageSent=false;
}
void setContentType(string contentType)
{
this->contentType=contentType;
}
void sendResponse(string content)
{
message="HTTP/1.1 200 OK\nContent-Type:"+contentType+"\nConnection: close\n\n";
message+=content;
if(messageSent==false) 
{
send(clientSocketDescriptor,message.c_str(),message.length(),0);
messageSent=true;
}
closesocket(clientSocketDescriptor);
}
};
class Error
{
string error;
public:
Error()
{
this->error="";
}
Error(string error)
{
this->error=error;
}
bool hasError()
{
return this->error.length()!=0;
}
string getError()
{
return this->error;
}
};
template<typename p2f,typename ...whatever>
class ThreadManager
{
private:
thread *ttt;
p2f funcAddress;
tuple<whatever...>t;
public:
ThreadManager(p2f f, whatever ...n):funcAddress(f),t(n...),ttt(NULL){}
~ThreadManager()
{
if(ttt)
{
ttt->join();
delete(ttt);
}
}
void start()
{
threadStarter(t, index_sequence_for<whatever...>());
}
template<size_t... c>
void threadStarter(tuple<whatever...> &t, index_sequence<c...>)
{
this->ttt=new thread(funcAddress,get<c>(t)...);
}
};
class HttpRock;
void processRequest(int clientSocketDescriptor,HttpRock httpRock);
class HttpRock // The Multithreaded server
{
string staticResources;
map<string,void(*)(Request &,Response &)> requestMappings;
public:
HttpRock()
{
this->staticResources="";
}
void useStatic(string folderPath)
{
this->staticResources=folderPath;
}
string getStaticResource()
{
return this->staticResources;
}
void get(string url, void (*callBack)(Request &,Response &))
{
this->requestMappings.insert(pair<string,void(*)(Request &,Response &)>(string(url),callBack));
}
bool hasResource(string resource)
{
map<string,void(*)(Request&,Response&)>::iterator i;
i=this->requestMappings.find(resource);
if(i==this->requestMappings.end()) return false;
return true;
}
auto getRequestMapping(string resource)
{
return this->requestMappings.find(resource);
}
void httpRock_listen(int port,void (*callBack)(Error &))
{
char message[101];
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
Error error("Unable to create socket");
callBack(error);
return;
}
serverSocketInformation.sin_family=AF_INET;
serverSocketInformation.sin_port=htons(port);
serverSocketInformation.sin_addr.s_addr=htonl(INADDR_ANY);
successCode=bind(serverSocketDescriptor,(struct sockaddr*)&serverSocketInformation, (unsigned int)sizeof(serverSocketInformation));
if(successCode<0)
{
Error error("Unable to bind server socket to port "+port);
WSACleanup();
callBack(error);
return;
}
listen(serverSocketDescriptor,10);
len=sizeof(clientSocketInformation);
while(1) // loop to accept connection
{
Error error;
callBack(error);
clientSocketDescriptor=accept(serverSocketDescriptor,(struct sockaddr*)&clientSocketInformation,&len);
if(clientSocketDescriptor<0)
{
Error error("Unable to connect to client connection");
closesocket(clientSocketDescriptor);
WSACleanup();
callBack(error);
return;
}
ThreadManager<void(*)(int, HttpRock),int, HttpRock> threadManager(processRequest,clientSocketDescriptor,*this);
threadManager.start();
} // the infinite loop related to accept method ends here
closesocket(clientSocketDescriptor);
closesocket(serverSocketDescriptor);
WSACleanup();
return;
}

};
void processRequest(int clientSocketDescriptor,HttpRock httpRock)
{
lock_guard<mutex> guard(mutualExclusionObject);
int bytesExtracted;
char requestBuffer[8192]; // 8192 1024 * 8
char responseBuffer[1024]; // A chunk of 1024
FILE *f;
int fileLength,i,rc;
bytesExtracted=recv(clientSocketDescriptor,requestBuffer,sizeof(requestBuffer),0);
if(bytesExtracted<0)
{

}
if(bytesExtracted==0)
{
}
else
{
requestBuffer[bytesExtracted]='\0';
cout<<requestBuffer<<endl;
char method[11];
char resource[1001];
int i,j;
for(i=0;requestBuffer[i]!=' ';i++)
{
method[i]=requestBuffer[i];
}
method[i]='\0';
i+=2;
for(j=0;requestBuffer[i]!=' ';j++,i++)
{
resource[j]=requestBuffer[i];
}
resource[j]='\0';
if(resource[0]=='\0')
{
cout<<"Sending index.html"<<endl;
string fileName=httpRock.getStaticResource()+"/index.html";
FILE *f=fopen(fileName.c_str(),"rb");
if(f==NULL)
{
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:text/html\nConnection: close\n\nResource %s not found",resource);
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
closesocket(clientSocketDescriptor);
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
// resource name is present
while(j>=0 && resource[j]!='.') j--;
if(resource[j]=='.')
{
char * mimeType=getMimeType(resource);
string fileName(httpRock.getStaticResource()+"/"+string(resource));
FILE *f=fopen(fileName.c_str(),"rb");
if(f==NULL)
{
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:%s\nConnection: close\n\nResource %s not found",resource);
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
closesocket(clientSocketDescriptor);
}
else
{
cout<<"Sending "<<resource<<endl;
fseek(f,0,2);
fileLength=ftell(f);
fseek(f,0,0);
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:%s\nContent-Length:%d\nConnection: close\n\n",mimeType,fileLength);
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
if(!(httpRock.hasResource(string("/")+resource)))
{
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:text/html\nConnection: close\n\nResource %s not found",resource);
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
closesocket(clientSocketDescriptor);
}
else
{
auto i=httpRock.getRequestMapping(string("/")+resource);
Request request;
Response response(clientSocketDescriptor);
i->second(request,response);
closesocket(clientSocketDescriptor);
}
}
}
}
}
// the following code is being written by WebSite Developer
int main()
{
HttpRock httpRock;

// request for html/css/js files should be server from xyz folder
httpRock.useStatic("xyz");

httpRock.get("/getCustomers",[](Request &request,Response &response)void{
response.setContentType("text/html");
string html;
html="<!DOCTYPE HTML>";
html+="<html>";
html+="<head>";
html+="<meta charset='utf-8'>";
html+="<title>Online Video Rental Library</title>";
html+="</head>";
html+="<body>";
html+="<h1>Admin DashBoard</h1>";
html+="<h3>Customers</h3>";
html+="Sudhir Gupta<br>";
html+="Ramesh Singh<br>";
html+="Gopal Sharma<br>";
html+="<br>";
html+="<a href='index.html'>Home</a>";
html+="</body>";
html+="</html>";
response.sendResponse(html); // this send should get called once only
response.sendResponse(html);
});

httpRock.httpRock_listen(6060,[](Error &error) void {
if(error.hasError())
{
cout<<error.getError()<<endl;
return;
}
cout<<"Http Rock Web Server is ready to accept request on port 6060"<<endl;
});
// because of the destructor of HttpRock, the main should not end
// till the server is not shutdown

return 0;
}
