#include<iostream>
#include<bl/uom>
#include<bl/uommanager>
using namespace inventory;
using namespace business_layer;
int main()
{
int code;
string title;
cout<<"Enter code : ";
cin>>code;
cout<<"Enter title : ";
cin>>title;
UnitOfMeasurement uom;
uom.setCode(code);
uom.setTitle(title);
UnitOfMeasurementManager manager;
try
{
manager.updateUnitOfMeasurement(&uom);
cout<<title<<" update"<<endl;
}catch(BLException blException)
{
if(blException.hasGenericException())
{
cout<<blException.getGenericException()<<endl;
}
if(blException.hasPropertyException("code"))
{
cout<<blException.getPropertyException("code")<<endl;
}
if(blException.hasPropertyException("title"))
{
cout<<blException.getPropertyException("title")<<endl;
}
}
return 0;
}