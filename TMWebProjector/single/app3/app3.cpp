#include<tmwp>
using namespace tmwp;
void feedMarks(Request & request, Response & response)
{
int rl=request.getInt("rl");
int p,c,m,e,h;
if(rl==101)
{
p=50;
c=55;
m=90;
e=60;
h=90;
request.setInt("physics",p);
request.setInt("chemistry",c);
request.setInt("maths",m);
request.setInt("english",e);
request.setInt("hindi",h);
}
if(rl==102)
{
p=82;
c=75;
m=94;
e=76;
h=92;
request.setInt("physics",p);
request.setInt("chemistry",c);
request.setInt("maths",m);
request.setInt("english",e);
request.setInt("hindi",h);
}
if(rl=103)
{
p=61;
c=56;
m=87;
e=57;
h=97;
request.setInt("physics",p);
request.setInt("chemistry",c);
request.setInt("maths",m);
request.setInt("english",e);
request.setInt("hindi",h);
}
request.forward("/MarkSheet.sct");
}
int main()
{
TMWebProjector server(5050);
server.onRequest("/feedMarks",feedMarks);
server.start();
}