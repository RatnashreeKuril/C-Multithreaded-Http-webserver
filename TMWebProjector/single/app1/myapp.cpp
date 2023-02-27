#include<tmwp>
#include<string.h>
#include<iostream>
#include<fstream>
using namespace std;
using namespace tmwp;
int compareStringIgnoreCase(const char *a, const char *b)
{
if(a==b) return 0;
if(a==NULL) return -1;
if(b==NULL) return 1;
char c,d;
for(;*a && *b;a++,b++)
{
c=*a;
if(c>=97 && c<=122) c=c-32;
d=*b;
if(d>=97 && d<=122) d=d-32;
if(c!=d) return c-d;
}
if(*a==*b) return 0;
c=*a;
if(c>=97 && c<=122) c=c-32;
d=*b;
if(d>=97 && d<=122) d=d-32;
return c-d;
}
class Student
{
private:
char rollNumber[50];
char name[50];
public:
Student()
{
}
Student(string rollNumber, string name)
{
strcpy(this->name,name.c_str());
strcpy(this->rollNumber,rollNumber.c_str());
}
void setName(string name)
{
strcpy(this->name,name.c_str());
}
string getName()
{
return string(this->name);
}
void setRollNumber(string rollNumber)
{
strcpy(this->rollNumber,rollNumber.c_str());
}
string getRollNumber()
{
return string(this->rollNumber);
}
};
void addStud(Request &request, Response &response)
{
string nm;
string rl;
ofstream f("student.dat", ios::app | ios::binary);
f.seekp(0,ios::beg);
nm=request.get("nm");
rl=request.get("rl");
cout<<nm<<endl;
cout<<rl<<endl;
Student s(rl,nm);
f.write((char *)&s, sizeof(Student));
f.close();
response.write("<!DOCTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>ABCL School, Ujjain</title></head><body><h2>Student added</h2><a href='index.html'>OK</a><br></body></html>");
response.close();
}
void getAllStudents(Request &request, Response &response)
{
fstream f("student.dat",ios::in | ios::binary);
if(f.fail())
{
response.write("<!DOCTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>ABCL School, Ujjain</title></head><body><h2>No student added</h2></body></html>");
response.close();
return;
}
Student student;
f.seekg(0,ios::beg);
int i=1;
char tmp[500];
response.write("<!DOCTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>ABCL School, Ujjain</title></head><body><Table border='1'><TR><td>S.No.</TD><TD>Roll No.</TD><TD>Name</TD></TR>");
while(1)
{
f.read((char *)&student,sizeof(Student));
if(f.fail()) break;
sprintf(tmp,"<tr><td>%d</td>",i);
response.write(tmp);
response.write("<td>");
string rl=student.getRollNumber();
response.write(rl);
response.write("<BR>");
response.write("</td>");
response.write("<td>");
response.write(student.getName());
response.write("</td>");
response.write("</tr>");
i++;
}
f.close();
response.write("</table></body></html>");
response.close();
}
void sendStudentEditForm(Request & request, Response &response)
{
string rl=request.get("rl");
fstream f("student.dat", ios::in | ios::binary);
f.seekg(0,ios::beg);
Student s;
char tmp[500];
while(true)
{
f.read((char *)&s, sizeof(s));
if(f.fail())break;
if(compareStringIgnoreCase((s.getRollNumber()).c_str(),rl.c_str())==0) break;
}
f.close();
response.write("<!DOCTYPE HTML>");
response.write("<html lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>ABCL School, Ujjain</title>");
response.write("</head>");
response.write("<body>");
response.write("student (Edit Module)");
response.write("<form method='get' action='updateStudent'>");
sprintf(tmp,"Roll number : %s",rl.c_str());
response.write(tmp);
sprintf(tmp,"<input type='hidden' id='rl' name='rl' value='%s'><br>",rl.c_str());
response.write(tmp);
sprintf(tmp,"Name<input type='text' id='nm' name='nm' value='%s'><br>",(s.getName()).c_str());
response.write(tmp);
response.write("<button type='submit'>Update</button>");
response.write("</form>");
response.write("<a href='index.html'>Home</a>");
response.write("</body>");
response.write("</html>");
response.close();
}
void updateStudentData(Request & request, Response &response)
{
string rl=request.get("rl");
string nm=request.get("nm");
fstream f("student.dat", ios::out | ios::in | ios::binary);
f.seekg(0,ios::beg);
Student s;
int pos;
while(true)
{
pos=f.tellg();
f.read((char *)&s, sizeof(s));
if(f.fail())break;
if(compareStringIgnoreCase((s.getRollNumber()).c_str(),rl.c_str())==0) break;
}
f.clear();
s.setRollNumber(rl);
s.setName(nm);
f.seekp(pos,ios::beg);
f.write((char *)&s, sizeof(s));
f.close();
response.write("<!DOCTYPE HTML>");
response.write("<html lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>ABCL School, Ujjain</title>");
response.write("</head>");
response.write("<body>");
response.write("Student (Edit Module)<br>");
response.write("<h3>Student updated</h3>");
response.write("<form method='get' action='index.html'>");
response.write("<button type='submit'>OK</button>");
response.write("</form>");
response.write("</body>");
response.write("</html>");
response.close();
}

void sendStudentDeleteConfirmationForm(Request &request, Response & response)
{
string rl=request.get("rl");
fstream f("student.dat", ios::in | ios::binary);
f.seekg(0,ios::beg);
Student s;
char tmp[500];
while(true)
{
f.read((char *)&s, sizeof(s));
if(f.fail())break;
if(compareStringIgnoreCase((s.getRollNumber()).c_str(),rl.c_str())==0) break;
}
f.close();
response.write("<!DOCTYPE HTML>");
response.write("<html lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>ABCL School, Ujjain</title>");
response.write("</head>");
response.write("<body>");
response.write("student (Delete Module)");
response.write("<form method='get' action='deleteStudent'>");
sprintf(tmp,"Roll number : %s",rl.c_str());
response.write(tmp);
sprintf(tmp,"<input type='hidden' id='rl' name='rl' value='%s'><br>",rl.c_str());
response.write(tmp);
sprintf(tmp,"Name : %s<br>",(s.getName()).c_str());
response.write(tmp);
response.write("<button type='submit'>Delete</button>");
response.write("</form>");
response.write("<a href='index.html'>Home</a>");
response.write("</body>");
response.write("</html>");
response.close();
}
void deleteStudentData(Request &request, Response &response)
{
string rl=request.get("rl");
fstream f("student.dat", ios::out | ios::in | ios::binary);
ofstream tmp("tmp.dat",ios::out | ios::binary);
f.seekg(0,ios::beg);
Student s;
while(true)
{
f.read((char *)&s, sizeof(s));
if(f.fail())break;
if(compareStringIgnoreCase((s.getRollNumber()).c_str(),rl.c_str())!=0) tmp.write((char *)&s,sizeof(s));
}
tmp.close();
f.close();
ifstream tmpF("tmp.dat",ios::in | ios::binary);
ofstream dataF("student.dat",ios::out | ios::binary);
while(true)
{
tmpF.read((char *)&s, sizeof(s));
if(tmpF.fail()) break;
dataF.write((char *)&s, sizeof(s));
}
tmpF.close();
dataF.close();
tmp.open("tmp.dat",ios::out | ios::binary);
tmp.close();
response.write("<!DOCTYPE HTML>");
response.write("<html lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>ABCL School, Ujjain</title>");
response.write("</head>");
response.write("<body>");
response.write("Student (Delete Module)<br>");
response.write("<h3>Student deleted</h3>");
response.write("<form method='get' action='index.html'>");
response.write("<button type='submit'>OK</button>");
response.write("</form>");
response.write("</body>");
response.write("</html>");
response.close();
}
int main()
{
TMWebProjector server(8080);
server.onRequest("/addStudent",addStud);
server.onRequest("/getStudent",getAllStudents);
server.onRequest("/editStudent",sendStudentEditForm);
server.onRequest("/updateStudent",updateStudentData);
server.onRequest("/confirmDeleteStudent",sendStudentDeleteConfirmationForm);
server.onRequest("/deleteStudent",deleteStudentData);
server.start();
return 0;
}