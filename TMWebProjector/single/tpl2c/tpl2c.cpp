#include<stdio.h>
#include<string.h>
#include<iostream>
#include<windows.h>
using namespace std;
int main()
{
WIN32_FIND_DATA ffd;
HANDLE hFind=INVALID_HANDLE_VALUE;
hFind=FindFirstFile("*.tpl", &ffd);
if(hFind==INVALID_HANDLE_VALUE)
{
return 0;
}
hFind=INVALID_HANDLE_VALUE;
hFind=FindFirstFile("*.tpl", &ffd);
if(hFind==INVALID_HANDLE_VALUE)
{
return 0;
}
FILE * headerFile=fopen("tpl.h","wb");
char fileName[101];
char header[500];
char functionName[101];
strcpy(header,"#ifndef __TPL\r\n");
strcat(header,"#define __TPL\r\n");
strcat(header,"#include<tmwp>\r\n");
strcat(header,"using namespace tmwp;\r\n");
fwrite(header,strlen(header),1,headerFile);
header[0]='\0';
do
{
strcpy(fileName,ffd.cFileName);
strcat(fileName,".cpp");
strcat(header,"void get");
int len=strlen(ffd.cFileName);
int g=len;
while(ffd.cFileName[g]!='.') g--;
int h=0;
if(ffd.cFileName[h]>=97 && ffd.cFileName[h]<=122) 
{
functionName[h]=ffd.cFileName[h]-32;
h++;
}
while(h<g)
{
functionName[h]=ffd.cFileName[h];
h++;
}
functionName[h]='\0';
strcat(header,functionName);
strcat(header,"_TPL(Request & request, Response & response);\r\n");
fwrite(header,strlen(header),1,headerFile);
header[0]='\0';
}while(FindNextFile(hFind, &ffd)!=0);
hFind=INVALID_HANDLE_VALUE;
hFind=FindFirstFile("*.tpl", &ffd);
if(hFind==INVALID_HANDLE_VALUE)
{
printf("Cannot find specified file\n");
return 0;
}
strcpy(header,"void registerTPLs(TMWebProjector * server)\r\n");
strcat(header,"{\r\n");
fwrite(header,strlen(header),1,headerFile);
header[0]='\0';
do
{
HANDLE hFile1, hFile2;
FILETIME ftCreate1, ftCreate2;
FILETIME ftLastWriteTime1;
FILETIME ftLastWriteTime2;
SYSTEMTIME stUTC, stLocal;
char fileName[101];
strcpy(fileName,ffd.cFileName);
strcat(fileName,".cpp");
hFile1 = CreateFile(ffd.cFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
hFile2=CreateFile(fileName,GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
GetFileTime(hFile1, &ftCreate1, NULL, &ftLastWriteTime1);
GetFileTime(hFile2, &ftCreate2, NULL, &ftLastWriteTime2);
int y=CompareFileTime(&ftLastWriteTime1,&ftLastWriteTime2);
int len=strlen(ffd.cFileName);
int g=len;
while(ffd.cFileName[g]!='.') g--;
int h=0;
if(ffd.cFileName[h]>=97 && ffd.cFileName[h]<=122) 
{
functionName[h]=ffd.cFileName[h]-32;
h++;
}
while(h<g)
{
functionName[h]=ffd.cFileName[h];
h++;
}
functionName[h]='\0';
strcpy(header,"server->onRequest(\"/");
strcat(header,ffd.cFileName);
strcat(header,"\",get");
strcat(header,functionName);
strcat(header,"_TPL);\r\n");
fwrite(header,strlen(header),1,headerFile);
header[0]='\0';
if(y==-1)
{
CloseHandle(hFile1);
CloseHandle(hFile2);
continue;
}
CloseHandle(hFile1);
CloseHandle(hFile2);
int i,rc,e,dc,si,f,flag,x;
long fileLength;
char responseBuffer[1024];
char tmp[1024];
char b[5];
char a[1024];
char key[1024];
strcpy(header,"#include<tmwp>\r\n");
strcat(header,"using namespace tmwp;\r\n");
strcat(header,"void get");
strcat(header,functionName);
strcat(header,"_TPL(Request & request, Response & response)\r\n");
strcat(header,"{\r\n");
strcpy(b,"$$${");
FILE * file=fopen(ffd.cFileName,"rb");
FILE * tmpFile=fopen(fileName,"wb");
fwrite(header,strlen(header),1,tmpFile);
header[0]='\0';
fseek(file,0,2);
fileLength=ftell(file);
fseek(file,0,0);
i=0;
flag=0;
x=0;
dc=0;
while(i<fileLength)
{
rc=fileLength-i;
if(rc>1024) rc=1024;
fread(&responseBuffer,rc,1,file);
responseBuffer[rc]='\0';
e=0;
f=0;
while(e<rc)
{
if(flag==1)
{
if(b[dc]!='\0')
{
while(responseBuffer[e]!='\0' && b[dc]!='\0' && responseBuffer[e]==b[dc])
{
e++;
dc++;
}
}
if(b[dc]=='\0')
{
while(responseBuffer[e]!='}' && responseBuffer[e]!='\0')
{
a[x]=responseBuffer[e];
e++;
x++;
}
a[x]='\0';
if(responseBuffer[e]=='\0')
{
tmp[f]='\0';
fwrite(tmp,strlen(tmp),1,tmpFile);
f=0;
tmp[0]='\0';
flag=0;
e=0;
continue;
}
if(responseBuffer[e]=='}')
{
if(f!=0)
{
strcpy(key,"response.write(\"");
fwrite(key,strlen(key),1,tmpFile);
tmp[f]='\0';
fwrite(tmp,strlen(tmp),1,tmpFile);
strcpy(key,"\");\r\n");
fwrite(key,strlen(key),1,tmpFile);
f=0;
tmp[0]='\0';
}
strcpy(key,"response.write(");
strcat(key,"request.getValue(\"");
strcat(key,a);
strcat(key,"\"));\r\n");
fwrite(key,strlen(key),1,tmpFile);
key[0]='\0';
a[0]='\0';
flag=0;
e++;
dc=0;
x=0;
}
}
}

if(responseBuffer[e]=='\r')
{
if(strlen(tmp)!=0)
{
strcpy(key,"response.write(\"");
fwrite(key,strlen(key),1,tmpFile);
tmp[f]='\0';
fwrite(tmp,strlen(tmp),1,tmpFile);
strcpy(header,"\");\r\n");
fwrite(header,strlen(header),1,tmpFile);
header[0]='\0';
f=0;
tmp[0]='\0';
}
e+=2;
}
if(responseBuffer[e]==b[dc])
{
si=e;
e++;
dc++;
while(responseBuffer[e]!='\0' && b[dc]!='\0' && responseBuffer[e]==b[dc])
{
e++;
dc++;
}
if(dc>0 && responseBuffer[e]=='\0')
{
flag=1;
break;
}
if(b[dc]!='\0' && responseBuffer[e]!='\0')
{
while(si<e)
{
if(responseBuffer[si]=='"')
{
tmp[f]='\\';
f++;
}
tmp[f]=responseBuffer[si];
f++;
si++;
}
si=0;
dc=0;
tmp[f]='\0';
}
if(b[dc]=='\0')
{
while(responseBuffer[e]!='}' && responseBuffer[e]!='\0')
{
a[x]=responseBuffer[e];
x++;
e++;
}
a[x]='\0';
if(responseBuffer[e]=='\0')
{
flag=1;
break;
}
else
if(responseBuffer[e]=='}')
{
if(f!=0)
{
strcpy(key,"response.write(\"");
tmp[f]='\0';
fwrite(key,strlen(key),1,tmpFile);
fwrite(tmp,strlen(tmp),1,tmpFile);
strcpy(key,"\");\r\n");
fwrite(key,strlen(key),1,tmpFile);
}
strcpy(key,"response.write(");
strcat(key,"request.getValue(\"");
strcat(key,a);
strcat(key,"\"));\r\n");
fwrite(key,strlen(key),1,tmpFile);
key[0]='\0';
e++;
dc=0;
x=0;
a[0]='\0';
f=0;
tmp[0]='\0';
}
}
}
else
{
if(responseBuffer[e]=='"')
{
tmp[f]='\\';
f++;
}
tmp[f]=responseBuffer[e];
f++;
e++;
tmp[f]='\0';
}
}
if(flag==1)
{
fwrite(tmp,si,1,tmpFile);
i+=rc;
continue;
}
tmp[f]='\0';
if(f!=0)
{
strcpy(key,"response.write(\"");
fwrite(key,strlen(key),1,tmpFile);
tmp[f]='\0';
fwrite(tmp,strlen(tmp),1,tmpFile);
strcpy(key,"\");\r\n");
fwrite(key,strlen(key),1,tmpFile);
f=0;
tmp[0]='\0';
}
key[0]='\0';
i+=rc;
}
strcpy(header,"response.close();\r\n");
strcat(header,"}\r\n");
fwrite(header,strlen(header),1,tmpFile);
header[0]='\0';
fclose(file);
fclose(tmpFile);
printf("%s generated\n",fileName);
printf("***********************************\n");
}while(FindNextFile(hFind, &ffd)!=0);
strcat(header,"}\r\n");
strcat(header,"#endif");
fwrite(header,strlen(header),1,headerFile);
header[0]='\0';
fclose(headerFile);
FindClose(hFind);
return 0;
}