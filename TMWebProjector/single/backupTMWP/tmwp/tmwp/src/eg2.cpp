#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
char* c=(char*)malloc(sizeof(char));
strncpy(c+0,"'",1);
c[1]='\0';
printf("%s",c);
free(c);
return 0;
}