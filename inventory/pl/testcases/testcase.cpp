#include<iostream>
#include<pl\iuom>
#include<pl\uom>
#include<pl\plexception>
#include<pl\iuommanager>
#include<pl\uommanager>
using namespace inventory;
using namespace presentation_layer;
using namespace std;
int main()
{
int ch;
while(1)
{
cout<<"1. Add unit of measurement"<<endl;
cout<<"2. Update unit of measurement"<<endl;
cout<<"3. Remove unit of measurement by code"<<endl;
cout<<"4. Remove unit of measurement by title"<<endl;
cout<<"5. Get unit of measurement by code"<<endl;
cout<<"6. Get unit of measurement by title"<<endl;
cout<<"7. Get list of unit of measurments"<<endl;
cout<<"8. Check unit of measurement exists by code"<<endl;
cout<<"9. Check unit of measurement exists by title"<<endl;
cout<<"10. Get unit of measurement count"<<endl;
cout<<"11. Exit."<<endl;
cout<<"Enter your choice : ";
cin>>ch;
if(ch<=0 || ch>11)
{
cout<<"Invalid choice";
return 0;
}
if(ch==1)
{
UnitOfMeasurement uom;
uom.setCode(0);
string title;
cout<<"Enter unit of measurement : ";
cin>>title;
uom.setTitle(title);
UnitOfMeasurementManager manager;
try
{
manager.addUnitOfMeasurement(&uom);
cout<<title<<" added"<<endl;
}catch(PLException plException)
{
if(plException.hasGenericException())
{
cout<<plException.getGenericException()<<endl;
}
if(plException.hasPropertyException("code"))
{
cout<<plException.getPropertyException("code")<<endl;
}
if(plException.hasPropertyException("title"))
{
cout<<plException.getPropertyException("title")<<endl;
}
}
}
if(ch==2)
{
int code;
cout<<"Enter code : ";
cin>>code;
string title;
cout<<"Enter unit of measurement : ";
cin>>title;
UnitOfMeasurement uom;
uom.setCode(code);
uom.setTitle(title);
UnitOfMeasurementManager manager;
try
{
manager.updateUnitOfMeasurement(&uom);
cout<<"Unit of measurement updated"<<endl;
}catch(PLException plException)
{
if(plException.hasGenericException())
{
cout<<plException.getGenericException()<<endl;
}
if(plException.hasPropertyException("code"))
{
cout<<plException.getPropertyException("code")<<endl;
}
if(plException.hasPropertyException("title"))
{
cout<<plException.getPropertyException("title")<<endl;
}
}
}
if(ch==3)
{
int code;
cout<<"Enter code : ";
cin>>code;
UnitOfMeasurementManager manager;
try
{
manager.removeUnitOfMeasurementByCode(code);
cout<<code<<" removed"<<endl;
}catch(PLException plException)
{
if(plException.hasGenericException())
{
cout<<plException.getGenericException()<<endl;
}
if(plException.hasPropertyException("code"))
{
cout<<plException.getPropertyException("code")<<endl;
}
if(plException.hasPropertyException("title"))
{
cout<<plException.getPropertyException("title")<<endl;
}
}
}
if(ch==4)
{
string title;
cout<<"Enter title : ";
cin>>title;
UnitOfMeasurementManager manager;
try
{
manager.removeUnitOfMeasurementByTitle(title);
cout<<title<<" removed"<<endl;
}catch(PLException plException)
{
if(plException.hasGenericException())
{
cout<<plException.getGenericException()<<endl;
}
if(plException.hasPropertyException("code"))
{
cout<<plException.getPropertyException("code")<<endl;
}
if(plException.hasPropertyException("title"))
{
cout<<plException.getPropertyException("title")<<endl;
}
}
}
if(ch==5)
{
int code;
abc::IUnitOfMeasurement *uom;
UnitOfMeasurementManager manager;
cout<<"Enter code : ";
cin>>code;
try
{
uom=manager.getUnitOfMeasurementByCode(code);
cout<<uom->getCode()<<" ,"<<uom->getTitle();
}catch(PLException plException)
{
if(plException.hasGenericException())
{
cout<<plException.getGenericException()<<endl;
}
if(plException.hasPropertyException("code"))
{
cout<<plException.getPropertyException("code")<<endl;
}
if(plException.hasPropertyException("title"))
{
cout<<plException.getPropertyException("title")<<endl;
}
}
}
if(ch==6)
{
string title;
abc::IUnitOfMeasurement *uom;
UnitOfMeasurementManager manager;
cout<<"Enter title : ";
cin>>title;
try
{
uom=manager.getUnitOfMeasurementByTitle(title);
cout<<uom->getCode()<<" ,"<<uom->getTitle();
}catch(PLException plException)
{
if(plException.hasGenericException())
{
cout<<plException.getGenericException()<<endl;
}
if(plException.hasPropertyException("code"))
{
cout<<plException.getPropertyException("code")<<endl;
}
if(plException.hasPropertyException("title"))
{
cout<<plException.getPropertyException("title")<<endl;
}
}
}
if(ch==7)
{
forward_list<abc::IUnitOfMeasurement *> *unitOfMeasurements;
UnitOfMeasurementManager manager;
unitOfMeasurements=manager.getUnitOfMeasurements();
forward_list<abc::IUnitOfMeasurement *>::iterator i=unitOfMeasurements->begin();
abc::IUnitOfMeasurement *plUnitOfMeasurement;
plUnitOfMeasurement=new UnitOfMeasurement;
while(i!=unitOfMeasurements->end())
{
plUnitOfMeasurement=*i;
cout<<plUnitOfMeasurement->getCode()<<", "<<plUnitOfMeasurement->getTitle()<<endl;
++i;
}
}
if(ch==8)
{
int code;
UnitOfMeasurementManager manager;
cout<<"Enter code : ";
cin>>code;
if(manager.UnitOfMeasurementCodeExists(code))
{
cout<<code<<" exists";
}
else
{
cout<<code<<" does not exists";
}
}
if(ch==9)
{
string title;
cout<<"Enter title : ";
cin>>title;
UnitOfMeasurementManager manager;
if(manager.UnitOfMeasurementTitleExists(title))
{
cout<<title<<" exists.";
}
else cout<<title<<" does not exists.";
}
if(ch==10)
{
UnitOfMeasurementManager manager;
cout<<manager.UnitOfMeasurementCount()<<endl;
}
if(ch==11)
{
break;
}
}
return 0;
}