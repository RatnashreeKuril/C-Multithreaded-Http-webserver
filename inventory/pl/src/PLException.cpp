#include<pl/plexception>
using namespace inventory;
using namespace presentation_layer;
PLException::PLException()
{
this->genericException="";
}
PLException::PLException(string genericException)
{
this->genericException=genericException;
}
PLException::PLException(const PLException &other)
{
this->genericException=other.genericException;
this->exceptions=other.exceptions;
}
PLException::~PLException() throw()
{
//do nothing
}
PLException & PLException::operator=(const PLException &other)
{
this->genericException=other.genericException;
this->exceptions=other.exceptions;
return *this;
}
const char * PLException::what() const throw()
{
return this->genericException.c_str();
}
int PLException::hasGenericException()
{
return this->genericException.length()>0;
}
void PLException::setGenericException(string genericException)
{
this->genericException=genericException;
}
string PLException::getGenericException()
{
return this->genericException;
}
void PLException::addPropertyException(string property,string exception)
{
this->exceptions.insert(pair<string,string>(property,exception));
}
string PLException::getPropertyException(string property)
{
map<string,string>::iterator i=this->exceptions.find(property);
if(i==this->exceptions.end())
{
return string("");
}
return i->second;
}
int PLException::hasPropertyException(string property)
{
return this->getPropertyException(property).length()>0;
}
int PLException::hasPropertyExceptions()
{
return this->getPropertyExceptionsCount()>0;
}
int PLException::hasExceptions()
{
int exceptionCount=0;
if(this->genericException.length()>0) exceptionCount++;
if(this->exceptions.size()>0) exceptionCount++;
return exceptionCount>0;
}
int PLException::getPropertyExceptionsCount()
{
return this->exceptions.size();
}