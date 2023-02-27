#include<tmsqlite>
#include<iostream>
using namespace std;
using namespace sqlite;
int main()
{
SqliteDB sqliteDB;
try
{
sqliteDB.open("student.db");
string sql="insert into student(name) values('suresh')";
sqliteDB.executeInsert(sql);
cout<<"Student added with ID : "<<sqliteDB.getGeneratedID()<<endl;
}catch(SQLiteException &sqliteException)
{
cout<<sqliteException.what()<<endl;
}
sqliteDB.close();
return 0;
}