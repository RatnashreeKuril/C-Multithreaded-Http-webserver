#include<sqlitedb>
#include<sqlite3.h>
#include<stdio.h>
#include<string.h>
#include<common/stringutils>
#include<sqliteexception>
#include<forward_list>
#include<map>
#include<iostream>
using namespace std;
using namespace sqlite;
using namespace stringutils;
bool Row::Comparator::operator()(string left, string right)
{
return left.c_str()<right.c_str();
}
int rowHandler(void *x, int columnCount, char**dataPtr, char **columnNamePtr)
{
forward_list<Row*>*list=(forward_list<Row*>*)x;
int e;
Row *row;
row=new Row;
for(e=0;e<columnCount;e++)
{
row->insertColumn(columnNamePtr[e],dataPtr[e]);
}
list->push_front(row);
return 0;
}
Row::Row()
{
columns=new map<string, string ,sqlite::Row::Comparator>;
}
Row::Row(const char *i,const char *j)
{
int e;
string column;
for(e=0;i[e]!='\0';e++)
{
column[e]=i[e];
}
column[e]='\0';
string data;
for(e=0;j[e]!='\0';e++)
{
data[e]=j[e];
}
data[e]='\0';
columns=new map<string, string ,sqlite::Row::Comparator>;
columns->insert(pair<string, string>(column,data));
}
Row::Row(const Row & other)
{
columns=new map<string, string, sqlite::Row::Comparator>;
columns=other.columns;
}
Row::~Row()
{

}
void Row::insertColumn(char *i, char *j)
{
int e;
string column;
for(e=0;i[e]!='\0';e++)
{
column[e]=i[e];
}
column[e]='\0';
string data;
for(e=0;j[e]!='\0';e++)
{
data[e]=j[e];
}
data[e]='\0';
columns->insert(pair<string , string>(column,data));
}
int Row::getInteger(const string &columnName)
{
string vColumnName=trimmed(columnName);
if(vColumnName.length()==0)
{
return 0;
}
map<string , string ,Comparator>::iterator i;
i=columns->find(vColumnName.c_str());
if(i==columns->end())
{
return 0;
}
string vData=i->second;
int e;
int data=0;
for(e=0;vData[e]!='\0';e++)
{
data=(vData[e]-48)+(data*10);
}
return data;
}
string Row::getString(const string &columnName)
{
string vColumnName=trimmed(columnName);
if(vColumnName.length()==0)
{
return string("");
}
map<string , string ,Comparator>::iterator i;
i=columns->find(vColumnName.c_str());
if(i==columns->end())
{
return string("");
}
else
{
string vData(i->second);
return vData;
}
}
Rows::Rows()
{
this->list=new forward_list<Row*>;
this->size=0;
}
Rows::Rows(forward_list<Row*>*list)
{
this->list=new forward_list<Row*>;
forward_list<Row*>::iterator i;
forward_list<Row*>::iterator e;
Row *row;
for(i=list->begin();i!=list->end();++i)
{
row=new Row;
row->columns=i->second->columns;
this->list->insert_after(e,row);
}
}
Rows::Rows(const Rows &)
{
}
Rows::~Rows()
{
}
void Rows::insertRow(const Row &)
{
}
Row Rows::getRow()
{
}
bool Rows::hasMoreRows()
{
}
SqliteDB::SqliteDB() throw(SQLiteException)
{
db=NULL;
errorMessage=NULL;
}
SqliteDB::SqliteDB(const string &fileName) throw(SQLiteException)
{
db=NULL;
errorMessage=NULL;
resultCode=sqlite3_open(fileName.c_str(),&db);
char arr[101];
if(resultCode!=SQLITE_OK)
{
sprintf(arr,"Unable to connect to %s\n",fileName.c_str());
sqlite3_close(db);
throw SQLiteException(arr);
}
}
SqliteDB::~SqliteDB() throw(SQLiteException)
{
}
SqliteDB & SqliteDB::operator=(const string &fileName) throw(SQLiteException)
{
resultCode=sqlite3_open(fileName.c_str(),&db);
char arr[101];
if(resultCode!=SQLITE_OK)
{
sprintf(arr,"Unable to connect to %s\n",fileName.c_str());
sqlite3_close(db);
throw SQLiteException(arr);
}
}
void SqliteDB::open(const string &fileName) throw(SQLiteException)
{
resultCode=sqlite3_open(fileName.c_str(),&db);
char arr[101];
if(resultCode!=SQLITE_OK)
{
sprintf(arr,"Unable to connect to %s\n",fileName.c_str());
sqlite3_close(db);
throw SQLiteException(arr);
}
}
int SqliteDB::getGeneratedID() throw(SQLiteException)
{
return sqlite3_last_insert_rowid(db);
}
void SqliteDB::executeInsert(const string &sql) throw(SQLiteException)
{
int e=0;
string c("insert");
char d;
string s=trimmed(sql);
while(s[e]!=' ' && c[e]!='\0')
{
if(s[e]>=65 && s[e]<=90)
{
d=s[e]+32;
}
else d=s[e];
if(d!=c[e])
{
throw SQLiteException("Invalid sql statement");
}
e++;
}
if(s[e]!=' ' || c[e]!='\0')
{
throw SQLiteException("Invalid sql statement");
}
char arr[101];
resultCode=sqlite3_exec(db,s.c_str(),0,0,&errorMessage);
if(resultCode!=SQLITE_OK)
{
sprintf(arr,"Unable to insert record, reason : %s\n",errorMessage);
sqlite3_free(errorMessage);
throw SQLiteException(arr);
}
}
void SqliteDB::executeUpdate(const string &sql) throw(SQLiteException)
{
int e=0;
string c("update");
char d;
string s=trimmed(sql);
while(s[e]!=' ' && c[e]!='\0')
{
if(s[e]>=65 && s[e]<=90)
{
d=s[e]+32;
}
else d=s[e];
if(d!=c[e])
{
throw SQLiteException("Invalid sql statement");
}
e++;
}
if(s[e]!=' ' || c[e]!='\0')
{
throw SQLiteException("Invalid sql statement");
}
char arr[101];
resultCode=sqlite3_exec(db,s.c_str(),0,0,&errorMessage);
if(resultCode!=SQLITE_OK)
{
sprintf(arr,"Unable to update record, reason : %s\n",errorMessage);
sqlite3_free(errorMessage);
throw SQLiteException(arr);
}
}
void SqliteDB::executeRemove(const string &sql) throw(SQLiteException)
{
int e=0;
string c("delete");
char d;
string s=trimmed(sql);
while(s[e]!=' ' && c[e]!='\0')
{
if(s[e]>=65 && s[e]<=90)
{
d=s[e]+32;
}
else d=s[e];
if(d!=c[e])
{
throw SQLiteException("Invalid sql statement");
}
e++;
}
if(s[e]!=' ' || c[e]!='\0')
{
throw SQLiteException("Invalid sql statement");
}
char arr[101];
resultCode=sqlite3_exec(db,s.c_str(),0,0,&errorMessage);
if(resultCode!=SQLITE_OK)
{
sprintf(arr,"Unable to remove record, reason : %s\n",errorMessage);
sqlite3_free(errorMessage);
throw SQLiteException(arr);
}
}
forward_list<Row*>* SqliteDB::selectRows(const string &) throw(SQLiteException)
{
int e=0;
string c("select");
char d;
string s=trimmed(sql);
while(s[e]!=' ' && c[e]!='\0')
{
if(s[e]>=65 && s[e]<=90)
{
d=s[e]+32;
}
else d=s[e];
if(d!=c[e])
{
throw SQLiteException("Invalid sql statement");
}
e++;
}
if(s[e]!=' ' || c[e]!='\0')
{
throw SQLiteException("Invalid sql statement");
}
forward_list<Row*>*list;
list=new forward_list<Row*>;
char arr[101];
resultCode=sqlite3_exec(db,s.c_str(),rowHandler,(void*)list,&errorMessage);
if(resultCode!=SQLITE_OK)
{
sprintf(arr,"Unable to fetch record, reason : %s\n",errorMessage);
sqlite3_free(errorMessage);
throw SQLiteException(arr);
}
return list;
}

int SqliteDB::isOpen() throw(SQLiteException)
{
if(db!=NULL) return true;
else return false;
}
void SqliteDB::close() throw(SQLiteException)
{
if(isOpen())
{
sqlite3_close(db);
db=NULL;
}
}
