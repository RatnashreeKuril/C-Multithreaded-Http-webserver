#include<pl/iuom>
#include<pl/uom>
#include<pl/iuommanager>
#include<pl/uommanager>
#include<common/stringutils>
#include<bl/iuom>
#include<bl/uom>
#include<bl/iuommanager>
#include<bl/uommanager>
#include<bl/blexception>
#include<forward_list>
using namespace stringutils;
using namespace inventory;
using namespace presentation_layer;
void UnitOfMeasurementManager::addUnitOfMeasurement(abc::IUnitOfMeasurement *unitOfMeasurement) throw(PLException)
{
PLException plException;
if(unitOfMeasurement==NULL)
{
plException.setGenericException("Unit of measurement required, NULL encountered");
throw plException;
}
int code=unitOfMeasurement->getCode();
string title=unitOfMeasurement->getTitle();
if(code!=0)
{
plException.addPropertyException("code","Code should be zero");
}
if(title.length()==0)
{
plException.addPropertyException("title","Title required, length is zero");
}
if(title.length()>50)
{
plException.addPropertyException("title","Title length cannot exceed 50");
}
if(plException.hasExceptions())
{
throw plException;
}
inventory::business_layer::UnitOfMeasurementManager manager;
try
{
inventory::business_layer::abc::IUnitOfMeasurement * blUnitOfMeasurement;
blUnitOfMeasurement=new inventory::business_layer::UnitOfMeasurement;
blUnitOfMeasurement->setTitle(title);
manager.addUnitOfMeasurement(blUnitOfMeasurement);
unitOfMeasurement->setCode(blUnitOfMeasurement->getCode());
delete blUnitOfMeasurement;
}catch(inventory::business_layer::BLException blException)
{
if(blException.hasGenericException())
{
plException.setGenericException(blException.getGenericException());
}
if(blException.hasPropertyException("code"))
{
plException.addPropertyException("code",blException.getPropertyException("code"));
}
if(blException.hasPropertyException("title"))
{
plException.addPropertyException("title",blException.getPropertyException("title"));
}
throw plException;
}
}
void UnitOfMeasurementManager::updateUnitOfMeasurement(abc::IUnitOfMeasurement *unitOfMeasurement) throw(PLException)
{
PLException plException;
int code=unitOfMeasurement->getCode();
string title=unitOfMeasurement->getTitle();
if(title.length()==0)
{
plException.addPropertyException("title","Title required, length is zero");
throw plException;
}
if(title.length()>50)
{
plException.addPropertyException("title","Title length cannot exceed 50");
throw plException;
}
inventory::business_layer::UnitOfMeasurementManager manager;
inventory::business_layer::abc::IUnitOfMeasurement *blUnitOfMeasurement;
try
{
blUnitOfMeasurement=new inventory::business_layer::UnitOfMeasurement;
blUnitOfMeasurement->setCode(code);
blUnitOfMeasurement->setTitle(title);
manager.updateUnitOfMeasurement(blUnitOfMeasurement);
}catch(inventory::business_layer::BLException blException)
{
if(blException.hasGenericException())
{
plException.setGenericException(blException.getGenericException());
}
if(blException.hasPropertyException("code"))
{
plException.addPropertyException("code",blException.getPropertyException("code"));
}
if(blException.hasPropertyException("title"))
{
plException.addPropertyException("title",blException.getPropertyException("title"));
}
throw plException;
}
}
void UnitOfMeasurementManager::removeUnitOfMeasurementByCode(int code) throw(PLException)
{
PLException plException;
if(code<=0)
{
plException.addPropertyException("code","Code should be greater than zero");
throw plException;
}
if(plException.hasExceptions())
{
throw plException;
}
inventory::business_layer::UnitOfMeasurementManager manager;
try
{
manager.removeUnitOfMeasurementByCode(code);
}catch(inventory::business_layer::BLException blException)
{
if(blException.hasGenericException())
{
plException.setGenericException(blException.getGenericException());
}
if(blException.hasPropertyException("code"))
{
plException.addPropertyException("code",blException.getPropertyException("code"));
}
if(blException.hasPropertyException("title"))
{
plException.addPropertyException("title",blException.getPropertyException("title"));
}
throw plException;
}
}
void UnitOfMeasurementManager::removeUnitOfMeasurementByTitle(string &title) throw(PLException)
{
PLException plException;
if(title.length()==0)
{
plException.setGenericException("Title required, length is zero");
throw plException;
}
if(title.length()>50)
{
plException.setGenericException("Title length cannot exceeed 50");
throw plException;
}
inventory::business_layer::UnitOfMeasurementManager manager;
try
{
manager.removeUnitOfMeasurementByTitle(title);
}catch(inventory::business_layer::BLException blException)
{
if(blException.hasGenericException())
{
plException.setGenericException(blException.getGenericException());
}
if(blException.hasPropertyException("code"))
{
plException.addPropertyException("code",blException.getPropertyException("code"));
}
if(blException.hasPropertyException("title"))
{
plException.addPropertyException("title",blException.getPropertyException("title"));
}
throw plException;
}
}
abc::IUnitOfMeasurement *UnitOfMeasurementManager::getUnitOfMeasurementByCode(int code) throw(PLException)
{
PLException plException;
inventory::business_layer::UnitOfMeasurementManager manager;
inventory::business_layer::abc::IUnitOfMeasurement *blUnitOfMeasurement;
abc::IUnitOfMeasurement *plUnitOfMeasurement;
try
{
blUnitOfMeasurement=manager.getUnitOfMeasurementByCode(code);
plUnitOfMeasurement=new UnitOfMeasurement;
plUnitOfMeasurement->setCode(blUnitOfMeasurement->getCode());
plUnitOfMeasurement->setTitle(blUnitOfMeasurement->getTitle());
delete blUnitOfMeasurement;
return plUnitOfMeasurement;
}catch(inventory::business_layer::BLException blException)
{
if(blException.hasGenericException())
{
plException.setGenericException(blException.getGenericException());
}
if(blException.hasPropertyException("code"))
{
plException.addPropertyException("code",blException.getPropertyException("code"));
}
if(blException.hasPropertyException("title"))
{
plException.addPropertyException("title",blException.getPropertyException("title"));
}
throw plException;
}
}
abc::IUnitOfMeasurement *UnitOfMeasurementManager::getUnitOfMeasurementByTitle(string &title) throw(PLException)
{
string vTitle=trimmed(title);
PLException plException;
inventory::business_layer::UnitOfMeasurementManager manager;
inventory::business_layer::abc::IUnitOfMeasurement *blUnitOfMeasurement;
abc::IUnitOfMeasurement *plUnitOfMeasurement;
try
{
blUnitOfMeasurement=manager.getUnitOfMeasurementByTitle(vTitle);
plUnitOfMeasurement=new UnitOfMeasurement;
plUnitOfMeasurement->setCode(blUnitOfMeasurement->getCode());
plUnitOfMeasurement->setTitle(blUnitOfMeasurement->getTitle());
delete blUnitOfMeasurement;
return plUnitOfMeasurement;
}catch(inventory::business_layer::BLException blException)
{
if(blException.hasGenericException())
{
plException.setGenericException(blException.getGenericException());
}
if(blException.hasPropertyException("code"))
{
plException.addPropertyException("code",blException.getPropertyException("code"));
}
if(blException.hasPropertyException("title"))
{
plException.addPropertyException("title",blException.getPropertyException("title"));
}
throw plException;
}
}
forward_list<abc::IUnitOfMeasurement *> *UnitOfMeasurementManager::getUnitOfMeasurements() throw(PLException)
{
inventory::business_layer::UnitOfMeasurementManager manager;
forward_list<inventory::business_layer::abc::IUnitOfMeasurement*>*blUnitOfMeasurementsList=manager.getUnitOfMeasurements();
inventory::business_layer::abc::IUnitOfMeasurement * blUnitOfMeasurement;
forward_list<inventory::business_layer::abc::IUnitOfMeasurement*>::iterator i=blUnitOfMeasurementsList->begin();
forward_list<abc::IUnitOfMeasurement *> *plUnitOfMeasurementsList;
abc::IUnitOfMeasurement * plUnitOfMeasurement;
forward_list<abc::IUnitOfMeasurement *>::iterator e=plUnitOfMeasurementsList->before_begin();
while(i!=blUnitOfMeasurementsList->end())
{
blUnitOfMeasurement=*i;
plUnitOfMeasurement=new UnitOfMeasurement;
plUnitOfMeasurement->setCode(blUnitOfMeasurement->getCode());
plUnitOfMeasurement->setTitle(blUnitOfMeasurement->getTitle());
e=plUnitOfMeasurementsList->insert_after(e,plUnitOfMeasurement);
++i;
}
for(i=blUnitOfMeasurementsList->begin();i!=blUnitOfMeasurementsList->end();++i)
{
blUnitOfMeasurement=*i;
delete blUnitOfMeasurement;
}
blUnitOfMeasurementsList->clear();
return plUnitOfMeasurementsList;
}
int UnitOfMeasurementManager::UnitOfMeasurementCodeExists(int code) throw(PLException)
{
inventory::business_layer::UnitOfMeasurementManager manager;
return manager.UnitOfMeasurementCodeExists(code);
}
int UnitOfMeasurementManager::UnitOfMeasurementTitleExists(string &title) throw(PLException)
{
inventory::business_layer::UnitOfMeasurementManager manager;
return manager.UnitOfMeasurementTitleExists(title);
}
int UnitOfMeasurementManager::UnitOfMeasurementCount() throw(PLException)
{
inventory::business_layer::UnitOfMeasurementManager manager;
int x=manager.UnitOfMeasurementCount();
return x;
}