#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
char * encoder(const char *query)
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


queryString[j]=query[i];
j++;
i++;
}
queryString[j]='\0';
char *eQuery=(char*)malloc(sizeof(char)*strlen(queryString));
strcpy(eQuery,queryString);
return eQuery;
}
int main()
{
string query("Ratna:kuril ");
cout<<query<<endl;
string dQuery(encoder(query.c_str()));
cout<<dQuery<<endl;
return 0;
}