#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<urlencoder>
using namespace tmwp;
char * URLEncoder::encoder(const char *query)
{
int i=0;
int j=0;
if(strlen(query)==0) return NULL;
char queryString[2048];
while(query[i]!=' ')
{
if(query[i]==':')
{
strncpy(queryString+j,"%3A",3);
i++;
j+=3;
continue;
}
if(query[i]=='/')
{
strncpy(queryString+j,"%2F",3);
i++;
j+=3;
continue;
}
if(query[i]=='?')
{
strncpy(queryString+j,"%3F",3);
i++;
j+=3;
continue;
}
if(query[i]=='#')
{
strncpy(queryString+j,"%23",3);
i++;
j+=3;
continue;
}
if(query[i]=='[')
{
strncpy(queryString+j,"%5B",3);
i++;
j+=3;
continue;
}
if(query[i]==']')
{
strncpy(queryString+j,"%5D",3);
i++;
j+=3;
continue;
}
if(query[i]=='@')
{
strncpy(queryString+j,"%40",3);
i++;
j+=3;
continue;
}
if(query[i]=='!')
{
strncpy(queryString+j,"%21",3);
i++;
j+=3;
continue;
}
if(query[i]=='$')
{
strncpy(queryString+j,"%24",3);
i++;
j+=3;
continue;
}
if(query[i]=='&')
{
strncpy(queryString+j,"%26",3);
i++;
j+=3;
continue;
}
if(query[i]==39)
{
strncpy(queryString+j,"%27",3);
i++;
j+=3;
continue;
}
if(query[i]=='(')
{
strncpy(queryString+j,"%28",3);
i++;
j+=3;
continue;
}
if(query[i]==')')
{
strncpy(queryString+j,"%29",3);
i++;
j+=3;
continue;
}
if(query[i]=='*')
{
strncpy(queryString+j,"%2A",3);
i++;
j+=3;
continue;
}
if(query[i]=='+')
{
strncpy(queryString+j,"%2B",3);
i++;
j+=3;
continue;
}
if(query[i]==',')
{
strncpy(queryString+j,"%2C",3);
i++;
j+=3;
continue;
}
if(query[i]==';')
{
strncpy(queryString+j,"%3B",3);
i++;
j+=3;
continue;
}
if(query[i]=='=')
{
strncpy(queryString+j,"%3D",3);
i++;
j+=3;
continue;
}
if(query[i]=='%')
{
strncpy(queryString+j,"%25",3);
i++;
j+=3;
continue;
}
if(query[i]==' ')
{
strncpy(queryString+j,"+",3);
i++;
j+=3;
continue;
}
queryString[j]=query[i];
j++;
i++;
}
queryString[j]='\0';
char *eQuery=(char*)malloc(sizeof(char)*strlen(queryString));
strcpy(eQuery,queryString);
return eQuery;
}
char * URLEncoder::decoder(const char *query)
{
int i=0;
int j=0;
if(strlen(query)==0) return NULL;
char queryString[2048];
while(query[i]!=' ')
{
if(query[i]=='+')
{
queryString[j]=' ';
i++;
j++;
continue;
}
if(query[i]=='%')
{
i++;
if(query[i]=='2')
{
i++;
if(query[i]=='F')
{
queryString[j]='/';
i++;
j++;
continue;
}
if(query[i]=='3')
{
queryString[j]='#';
i++;
j++;
continue;
}
if(query[i]=='1')
{
queryString[j]='!';
i++;
j++;
continue;
}
if(query[i]=='4')
{
queryString[j]='$';
i++;
j++;
continue;
}
if(query[i]=='6')
{
queryString[j]='&';
i++;
j++;
continue;
}
if(query[i]=='7')
{
queryString[j]=39;
i++;
j++;
continue;
}
if(query[i]=='8')
{
queryString[j]='(';
i++;
j++;
continue;
}
if(query[i]=='9')
{
queryString[j]=')';
i++;
j++;
continue;
}
if(query[i]=='A')
{
queryString[j]='*';
i++;
j++;
continue;
}
if(query[i]=='B')
{
queryString[j]='+';
i++;
j++;
continue;
}
if(query[i]=='C')
{
queryString[j]=',';
i++;
j++;
continue;
}
if(query[i]=='5')
{
queryString[j]='%';
i++;
j++;
continue;
}
if(query[i]=='4')
{
queryString[j]='$';
i++;
j++;
continue;
}
}// if condition for 2
if(query[i]=='3')
{
i++;
if(query[i]=='A')
{
queryString[j]=':';
i++;
j++;
continue;
}
if(query[i]=='F')
{
queryString[j]='?';
i++;
j++;
continue;
}
if(query[i]=='B')
{
queryString[j]=';';
i++;
j++;
continue;
}
if(query[i]=='D')
{
queryString[j]='=';
i++;
j++;
continue;
}
}// if condition for 3
if(query[i]=='4')
{
i++;
if(query[i]=='0')
{
queryString[j]='@';
i++;
j++;
continue;
}
}// if condition for 4
if(query[i]=='5')
{
i++;
if(query[i]=='B')
{
queryString[j]='[';
i++;
j++;
continue;
}
if(query[i]=='D')
{
queryString[j]=']';
i++;
j++;
continue;
}
}//if condition for 5
}// if condition for %
queryString[j]=query[i];
i++;j++;
}

queryString[j]='\0';
char *dQuery=(char *)malloc(sizeof(char)*strlen(queryString));
strcpy(dQuery,queryString);
return dQuery;
}