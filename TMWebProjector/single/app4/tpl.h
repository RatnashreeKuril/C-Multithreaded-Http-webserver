#ifndef __TPL
#define __TPL
#include<tmwp>
using namespace tmwp;
void getAbcd_TPL(Request & request, Response & response);
void getEfgh_TPL(Request & request, Response & response);
void getErrorPage_TPL(Request & request, Response & response);
void registerTPLs(TMWebProjector * server)
{
server->onRequest("/abcd.tpl",getAbcd_TPL);
server->onRequest("/efgh.tpl",getEfgh_TPL);
server->onRequest("/ErrorPage.tpl",getErrorPage_TPL);
}
#endif