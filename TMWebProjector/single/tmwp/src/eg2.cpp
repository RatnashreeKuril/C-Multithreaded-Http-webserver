#include<stdio.h>
int main()
{
File *f=fopen("tmp.tmp","r");
char responseBuffer[1024];
int e=0;
int doller=0;
string key;
string value;
int f;
while(e<rc)
{
while(responseBuffer[e]=='$')
{
doller++;
}
if(doller==3)
{
doller=0;
e++;
if(responseBuffer[e]=='{')
{
f=0;
while(responseBuffer[e]!='}')
{
key[f]=responseBuffer[e];
e++;
f++;
}
value=getValue(key);

}
}
e++;
}


return 0;
}