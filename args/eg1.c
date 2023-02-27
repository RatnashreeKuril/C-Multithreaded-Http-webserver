#include<stdio.h>
#include<stdarg.h>
int getSum(int numberOfElements, ...)
{

int total,e;
va_list list;
va_start(list,numberOfElements);
total=0;
for(e=1;e<=numberOfElements;e++)
{
total+=va_arg(list,int);
}
va_end(list);
return total;
}
int main()
{
int sum;
sum=getSum(3,10,20,30);
printf("%d\n",sum);
sum=getSum(2,10,20);
printf("%d\n",sum);

return 0;
}