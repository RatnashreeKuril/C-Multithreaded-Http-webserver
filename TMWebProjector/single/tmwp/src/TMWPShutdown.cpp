#include<iostream>
#include<tmwp>
using namespace std;
using namespace tmwp;
class TMWPShutdown
{
private:
TMWebProjector *server;
public:
void initilize(TMWebProjector * server)
{
this->server=server;
}
void close()
{
this->server->close();
}
};
int main()
{
TMWPShutdown tmwpShutdown;
tmwpShutdown.close();
return 0;
}