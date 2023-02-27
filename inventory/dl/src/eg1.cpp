#include<iostream>
#include<sqlite3.h>
#include<stdio.h>
#include<string.h>
using namespace std;
int main()
{
sqlite3 *db;
int resultCode;
char *errorMessage;
char sql[1001];
sqlite3_stmt *preparedStatement;
resultCode=sqlite3_open("student.db",&db);
if(resultCode!=SQLITE_OK)
{
cout<<"unable to connect to student.db"<<endl;
}
strcpy(sql,"select * from student");
resultCode=sqlite3_prepare_v2(db,sql,-1,&preparedStatement,NULL);
if(resultCode!=SQLITE_OK)
{
cout<<"sql error"<<endl;
cout<<resultCode<<endl;
sqlite3_close(db);
return 0;
}
resultCode=sqlite3_bind_text(preparedStatement,1,"ravi",strlen("ravi"),NULL);
if(resultCode!=SQLITE_OK)
{
cout<<"Binding error"<<endl;
sqlite3_close(db);
return 0;
}
resultCode=sqlite3_step(preparedStatement);
if(resultCode!=SQLITE_DONE)
{
cout<<"Unable to fetch data"<<endl;
sqlite3_finalize(preparedStatement);
sqlite3_close(db);
return 0;
}
cout<<"Record inserted"<<endl;
return 0;
}