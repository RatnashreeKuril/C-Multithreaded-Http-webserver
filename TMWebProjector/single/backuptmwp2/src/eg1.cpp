#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;
int main()
{
int x,y;
cout<<"Enter value for x : ";
cin>>x;
cout<<"Enter value for y : ";
cin>>y;
FILE *f=fopen("abcd.xyz","rb");
char arr[100];
char tmp[100];
while(1)
{
fread(arr,100,1,f);
arr[strlen(arr)-1]='\0';
if(feof(f)) break;
for(int e=0;e<strlen(arr);e++)
{
if(arr[e]=='$')
{
int i=e;
e++;
if(arr[e]=='{')
{
e++;
if(arr[e]=='x')
{
strncpy(tmp,arr,i);
tmp[i]='\0';
char a[10];
sprintf(a,"%d",x);
strcat(tmp,a);
e+=2;
strcat(tmp,arr+e);
strcpy(arr,tmp);
}
if(arr[e]=='y')
{
strncpy(tmp,arr,i);
tmp[i]='\0';
char a[50];
sprintf(a,"%d",y);
strcat(tmp,a);
e+=2;
strcat(tmp,arr+e);
strcpy(arr,tmp);
}
}
}
}
printf("%s",arr);
}
fclose(f);
for(int e=0;e<strlen(arr);e++)
{
if(arr[e]=='$')
{
int i=e;
e++;
if(arr[e]=='{')
{
e++;
if(arr[e]=='x')
{
strncpy(tmp,arr,i-1);
sprintf(tmp+1,"%s",x);
strcat(tmp,arr+(i+1));
strcpy(arr,tmp);
}
if(arr[e]=='y')
{
strncpy(tmp,arr,i-1);
sprintf(tmp+1,"%s",y);
strcat(tmp,arr+(i+1));
strcpy(arr,tmp);
}
}
}
}
printf("%s",arr);
return 0;
}