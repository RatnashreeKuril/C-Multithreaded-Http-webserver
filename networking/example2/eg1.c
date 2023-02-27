#include<stdio.h>
#include<string.h>
int main()
{
char *fileName;
strcpy(fileName,"abcd.db");
FILE *f;
f=fopen(fileName,"a");
fclose(f);
return 0;
}