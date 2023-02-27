#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
int *x;
int e=0;
while(e<=100)
{
x=(int *)malloc(sizeof(int)*10);
e++;
}
printf("Memory allocated\n");
return 0;
}