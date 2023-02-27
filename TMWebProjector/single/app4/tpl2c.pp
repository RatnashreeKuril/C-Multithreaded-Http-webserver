#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;
int main()
{
int i;
long fileLength;
char responseBuffer[1024];
char tmp[3000];
FILE * file=fopen("ErrorPage.tpl","rb");
if(file==NULL)
{
printf("File does not exists");
return 0;
}
FILE * tmpFile=fopen("ErrorPage.tpl.cpp","wb");
fseek(file,0,2);
fileLength=ftell(file);
fseek(file,0,0);
//sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:text/html\nConnection: close\n\n");
//send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
i=0;
int dc=0;
while(i<fileLength)
{
rc=fileLength-i;
if(rc>1024) rc=1024;
fread(&responseBuffer, rc, 1, file);
int e=0;
int si;
while(e<=rc)
{
if(responseBuffer[e]=='$' && e<=rc)
{
si=e;
e++;
dc++;
while(responseBuffer[e]=='$' && e<=rc)
{
e++;
dc++;
}

}

if(dc==3 && e<=1024 && responseBuffer[e]=='{')
{
char a[10];
int f=0;
e++;
while(responseBuffer[e]!='}')
{
a[f]=responseBuffer[e];
e++;f++;
}
a[f]='\0';
string value("Invalid choice");
char b[value.length()];
sprintf(b,"%s",value.c_str());
strncpy(tmp,responseBuffer,si);
strcat(tmp,b);
strcat(tmp,responseBuffer+e+1);
dc=0;
f=0;
}
if(dc>0 && e>=1024)
{
break;
}


e++;
}
if(dc>0 && e>=1024)
{
fwrite(tmp,rc-dc,1,tmpFile);
i+=rc;
continue;
}


fwrite(tmp,rc,1,tmpFile);
i+=rc;
}
fclose(file);
fclose(tmpFile);
return 0;
}