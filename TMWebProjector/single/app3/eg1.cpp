#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
#include<map>
using namespace std;
class Comparator
{
public:
bool operator()(char *left ,char *rigth)
{
return strcmp(left,rigth)<0;
}
};
class Student
{
public:
char *name;
char *rollNumber;
};
int main()
{
map<char *,Student *,Comparator>students;
char *name;
char *rollNumber;
name=(char *)malloc(sizeof(char)*7);
rollNumber=(char *)malloc(sizeof(char)*3);
strcpy(name,"Ramesh");
strcpy(rollNumber,"10");
Student *s1=new Student;
s1->name=(char *)malloc(sizeof(char)*7);
s1->rollNumber=(char *)malloc(sizeof(char)*3);
strcpy(s1->name,name);
strcpy(s1->rollNumber,rollNumber);
students.insert(pair<char *, Student *>(s1->rollNumber,s1));
free(name);
free(rollNumber);


name=(char *)malloc(sizeof(char)*7);
rollNumber=(char *)malloc(sizeof(char)*3);
strcpy(name,"Somesh");
strcpy(rollNumber,"11");
Student *s2=new Student;
s2->name=(char *)malloc(sizeof(char)*7);
s2->rollNumber=(char *)malloc(sizeof(char)*3);
strcpy(s2->name,name);
strcpy(s2->rollNumber,rollNumber);
students.insert(pair<char *, Student *>(s2->rollNumber,s2));
free(name);
free(rollNumber);


name=(char *)malloc(sizeof(char)*7);
rollNumber=(char *)malloc(sizeof(char)*3);
strcpy(name,"Kamosh");
strcpy(rollNumber,"12");
Student *s3=new Student;
s3->name=(char *)malloc(sizeof(char)*7);
s3->rollNumber=(char *)malloc(sizeof(char)*3);
strcpy(s3->name,name);
strcpy(s3->rollNumber,rollNumber);
students.insert(pair<char *, Student *>(s3->rollNumber,s3));
free(name);
free(rollNumber);

name=(char *)malloc(sizeof(char)*7);
rollNumber=(char *)malloc(sizeof(char)*3);
strcpy(name,"Lamosh");
strcpy(rollNumber,"13");
Student *s4=new Student;
s4->name=(char *)malloc(sizeof(char)*7);
s4->rollNumber=(char *)malloc(sizeof(char)*3);
strcpy(s4->name,name);
strcpy(s4->rollNumber,rollNumber);
students.insert(pair<char *, Student *>(s4->rollNumber,s4));
free(name);
free(rollNumber);

map<char *,Student *,Comparator>::iterator i;
Student *s;
for(i=students.begin();i!=students.end();++i)
{
printf("%s\n",i->first);
s=i->second;
printf("Value : (%s, %s)\n",s->name,s->rollNumber);
}
char *key;
Student *d;
for(i=students.begin();i!=students.end();++i)
{
printf("%s\n",i->first);
free(i->first);
d=i->second;
printf("%s\n",d->name);
free(d->name);
students.erase(i);
}
printf("Cleared map\n");
students.clear();
return 0;
}