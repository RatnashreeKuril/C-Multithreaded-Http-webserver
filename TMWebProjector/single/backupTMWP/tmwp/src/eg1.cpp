#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;
int main()
{
int x,y;
int sp;
int e;
cout<<"Enter value for x : ";
cin>>x;
cout<<"Enter value for y : ";
cin>>y;
FILE *f=fopen("abcd.xyz","r");
char arr[101];
while(1)
{
fgets(arr,101,f);
if(feof(f)) break;
e=0;
while(arr[e]!='\0')
{
if(arr[e]=='$')
{
int sp=e;
e+=2;
char a[10];
int f=0;
while(arr[e]!='}')
{
a[f]=arr[e];
f++;
e++;
}
a[f]='\0';
int tmpLen=strlen(a)+strlen(arr)-e;
char tmp[tmpLen];
if(strcmp(a,"x")==0)
{
sprintf(tmp,"%d",x);
}
else
{
sprintf(tmp,"%d",y);
}
strcat(tmp,arr+e+1);
arr[sp]='\0';
strcat(arr,tmp);
e=sp;
}
else
{
e++;
}
}
printf("%s",arr);
}
fclose(f);
e=0;
while(arr[e]!='\0')
{
if(arr[e]=='$')
{
int sp=e;
e+=2;
char a[10];
int f=0;
while(arr[e]!='}')
{
a[f]=arr[e];
f++;
e++;
}
a[f]='\0';
int tmpLen=strlen(a)+strlen(arr)-e;
char tmp[tmpLen];
sprintf(tmp,"%d",a);
strcat(tmp,arr+e+1);
arr[sp]='\0';
strcat(arr,tmp);
e=sp;
}
else
{
e++;
}
}
printf("%s",arr);
return 0;
}