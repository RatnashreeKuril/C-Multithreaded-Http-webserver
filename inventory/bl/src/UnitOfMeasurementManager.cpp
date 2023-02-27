#include<bl/iuom>
#include<bl/uom>
#include<bl/iuommanager>
#include<bl/uommanager>
#include<common/stringutils>
#include<dl/iuom>
#include<dl/uom>
#include<dl/iuomdao>
#include<dl/uomdao>
#include<dl/daoexception>
#include<forward_list>
#include<map>
using namespace stringutils;
using namespace inventory;
using namespace business_layer;
UnitOfMeasurementManager::DataModel UnitOfMeasurementManager::dataModel;
bool UnitOfMeasurementTitleComparator::operator()(string *left, string *right)
{
return compareStringIgnoreCase(left->c_str(), right->c_str())<0;
}
UnitOfMeasurementManager::DataModel::DataModel()
{
populateDataStructure();
}
UnitOfMeasurementManager::DataModel::~DataModel()
{
map<int, _UnitOfMeasurement*>::iterator i;
i=dataModel.codeWiseMap.begin();
while(i!=dataModel.codeWiseMap.end())
{
delete i->second;
dataModel.codeWiseMap.erase(i);
++i;
}
dataModel.codeWiseMap.clear();
// releasing title wise map
map<string *, _UnitOfMeasurement*>::iterator e;
e=dataModel.titleWiseMap.begin();
while(e!=dataModel.titleWiseMap.end())
{
delete e->first;
delete e->second;
dataModel.titleWiseMap.erase(e);
++e;
}
dataModel.titleWiseMap.clear();
}
void UnitOfMeasurementManager::DataModel::populateDataStructure()
{
forward_list<inventory::data_layer::abc::IUnitOfMeasurement *> *dlUnitOfMeasurements;
inventory::data_layer::UnitOfMeasurementDAO unitOfMeasurementDAO;
try
{
dlUnitOfMeasurements=unitOfMeasurementDAO.getAll();
forward_list<inventory::data_layer::abc::IUnitOfMeasurement *>::iterator i;
inventory::data_layer::abc::IUnitOfMeasurement * dlUnitOfMeasurement;
_UnitOfMeasurement *blUnitOfMeasurement;
int code;
string *title;
for(i=dlUnitOfMeasurements->begin();i!=dlUnitOfMeasurements->end();++i)
{
dlUnitOfMeasurement=*i;
code=dlUnitOfMeasurement->getCode();
title=new string(dlUnitOfMeasurement->getTitle());
blUnitOfMeasurement=new _UnitOfMeasurement;
blUnitOfMeasurement->code=code;
blUnitOfMeasurement->title=title;
dataModel.codeWiseMap.insert(pair<int, _UnitOfMeasurement *>(blUnitOfMeasurement->code, blUnitOfMeasurement));
dataModel.titleWiseMap.insert(pair<string* ,_UnitOfMeasurement *>(blUnitOfMeasurement->title, blUnitOfMeasurement));
delete dlUnitOfMeasurement;
}
dlUnitOfMeasurements->clear();
delete dlUnitOfMeasurements;
}catch(inventory::data_layer::DAOException &daoException)
{
// no need to do anything
}
}
UnitOfMeasurementManager::UnitOfMeasurementManager()
{

}
void UnitOfMeasurementManager::addUnitOfMeasurement(abc::IUnitOfMeasurement *unitOfMeasurement) throw(BLException)
{
BLException blException;
if(unitOfMeasurement==NULL)
{
blException.setGenericException("Unit of measurement required, NULL encountered");
throw blException;
}
int code=unitOfMeasurement->getCode();
string title=unitOfMeasurement->getTitle();
if(code!=0)
{
blException.addPropertyException("code","Code should be zero");
}
if(title.length()==0)
{
blException.addPropertyException("title","Title required, length is zero");
}
if(title.length()>50)
{
blException.addPropertyException("title","Title length cannot exceed 50");
}
if(blException.hasExceptions())
{
throw blException;
}
map<string *, _UnitOfMeasurement *, UnitOfMeasurementTitleComparator>::iterator i;
i=dataModel.titleWiseMap.find(&title);
if(i!=dataModel.titleWiseMap.end())
{
blException.addPropertyException("title", "Given title exists");
throw blException;
}
inventory::data_layer::UnitOfMeasurementDAO unitOfMeasurementDAO;
try
{
inventory::data_layer::abc::IUnitOfMeasurement * dlUnitOfMeasurement;
dlUnitOfMeasurement=new inventory::data_layer::UnitOfMeasurement;
dlUnitOfMeasurement->setTitle(title);
unitOfMeasurementDAO.add(dlUnitOfMeasurement);
unitOfMeasurement->setCode(dlUnitOfMeasurement->getCode());
string *t=new string(title);                                             
_UnitOfMeasurement *blUnitOfMeasurement;
blUnitOfMeasurement=new _UnitOfMeasurement;
blUnitOfMeasurement->code=dlUnitOfMeasurement->getCode();
blUnitOfMeasurement->title=t;
dataModel.codeWiseMap.insert(pair<int, _UnitOfMeasurement *>(code, blUnitOfMeasurement));
dataModel.titleWiseMap.insert(pair<string *, _UnitOfMeasurement *>(t, blUnitOfMeasurement));
delete dlUnitOfMeasurement;
}catch(inventory::data_layer::DAOException daoException)
{
BLException blException;
blException.setGenericException(string(daoException.what()));
throw blException;
}
}
void UnitOfMeasurementManager::updateUnitOfMeasurement(abc::IUnitOfMeasurement *unitOfMeasurement) throw(BLException)
{
BLException blException;
if(unitOfMeasurement==NULL)
{
blException.setGenericException("Unit of measurement required, NULL encountered");
throw blException;
}
int code=unitOfMeasurement->getCode();
string title=unitOfMeasurement->getTitle();
if(code<=0)
{
blException.addPropertyException("code","Code should be greater than zero");
}
if(title.length()==0)
{
blException.addPropertyException("title","Title required, length is zero");
}
if(title.length()>50)
{
blException.addPropertyException("title","Title length cannot exceed 50");
}
if(blException.hasExceptions())
{
throw blException;
}
map<int, _UnitOfMeasurement *>::iterator e;
e=dataModel.codeWiseMap.find(code);
if(e->first!=code)
{
blException.addPropertyException("code","Invalid unit of measurement code");
throw blException;
}
_UnitOfMeasurement * blUnitOfMeasurement;
map<string *, _UnitOfMeasurement *, UnitOfMeasurementTitleComparator>::iterator i;
i=dataModel.titleWiseMap.begin();
string *t=new string(title);
while(i!=dataModel.titleWiseMap.end())
{
blUnitOfMeasurement=i->second;
if(blUnitOfMeasurement->code!=code && compareStringIgnoreCase(i->first->c_str(),t->c_str())==0)
{
blException.addPropertyException("title","Given title already exists");
throw blException;
}
++i;
}
inventory::data_layer::UnitOfMeasurementDAO unitOfMeasurementDAO;
try
{
inventory::data_layer::abc::IUnitOfMeasurement * dlUnitOfMeasurement;
dlUnitOfMeasurement=new inventory::data_layer::UnitOfMeasurement;
dlUnitOfMeasurement->setCode(code);
dlUnitOfMeasurement->setTitle(title);
unitOfMeasurementDAO.update(dlUnitOfMeasurement);
delete dlUnitOfMeasurement;                                         
blUnitOfMeasurement=e->second;
string *vTitle=blUnitOfMeasurement->title;
i=dataModel.titleWiseMap.find(vTitle);
delete i->first;
delete i->second;
dataModel.titleWiseMap.erase(i);
dataModel.codeWiseMap.erase(code);
blUnitOfMeasurement->code=code;
blUnitOfMeasurement->title=t;
dataModel.codeWiseMap.insert(pair<int, _UnitOfMeasurement *>(code, blUnitOfMeasurement));
dataModel.titleWiseMap.insert(pair<string *, _UnitOfMeasurement *>(t, blUnitOfMeasurement));
}catch(inventory::data_layer::DAOException daoException)
{
BLException blException;
blException.setGenericException(string(daoException.what()));
throw blException;
}
}
void UnitOfMeasurementManager::removeUnitOfMeasurementByCode(int code) throw(BLException)
{
BLException blException;
if(code<=0)
{
blException.addPropertyException("code","Code should be greater than zero");
throw blException;
}
if(blException.hasExceptions())
{
throw blException;
}
inventory::data_layer::UnitOfMeasurementDAO unitOfMeasurementDAO;
map<int, _UnitOfMeasurement *>::iterator i;
map<string *, _UnitOfMeasurement *>::iterator e;
i=dataModel.codeWiseMap.find(code);
if(i->first!=code)
{
blException.addPropertyException("code","Invalid unit of measurement code");
throw blException;
}
try
{
unitOfMeasurementDAO.remove(code);
_UnitOfMeasurement *blUnitOfMeasurement;
blUnitOfMeasurement=i->second;
e=dataModel.titleWiseMap.find(blUnitOfMeasurement->title);
delete e->first;
delete e->second;
dataModel.titleWiseMap.erase(e);
delete i->second;
dataModel.codeWiseMap.erase(i);
delete blUnitOfMeasurement;
}catch(inventory::data_layer::DAOException daoException)
{
BLException blException;
blException.setGenericException(string(daoException.what()));
throw blException;
}
}
void UnitOfMeasurementManager::removeUnitOfMeasurementByTitle(string &title) throw(BLException)
{
BLException blException;
if(title.length()==0)
{
blException.setGenericException("Title required, length is zero");
throw blException;
}
if(title.length()>50)
{
blException.setGenericException("Title length cannot exceeed 50");
throw blException;
}
map<string *, _UnitOfMeasurement *, UnitOfMeasurementTitleComparator>::iterator i;
string *t=new string(title);
i=dataModel.titleWiseMap.find(t);
if(i==dataModel.titleWiseMap.end())
{
blException.addPropertyException("title", "Invalid unit of measurement");
throw blException;
}
_UnitOfMeasurement *blUnitOfMeasurement;
inventory::data_layer::UnitOfMeasurementDAO unitOfMeasurementDAO;
try
{
blUnitOfMeasurement=i->second;
unitOfMeasurementDAO.remove(blUnitOfMeasurement->code);
dataModel.codeWiseMap.erase(blUnitOfMeasurement->code);
dataModel.titleWiseMap.erase(blUnitOfMeasurement->title);
delete blUnitOfMeasurement;
return;
}catch(inventory::data_layer::DAOException daoException)
{
BLException blException;
blException.setGenericException(string(daoException.what()));
}
}
abc::IUnitOfMeasurement *UnitOfMeasurementManager::getUnitOfMeasurementByCode(int code) throw(BLException)
{
BLException blException;
if(code<=0)
{
blException.setGenericException(string("Code should be greater than zero"));
throw blException;
}
map<int, _UnitOfMeasurement *>::iterator i;
i=dataModel.codeWiseMap.find(code);
if(i==dataModel.codeWiseMap.end())
{
blException.setGenericException(string("Invalid unit of measurement code"));
throw blException;
}
abc::IUnitOfMeasurement *unitOfMeasurement;
_UnitOfMeasurement *_unitOfMeasurement;
_unitOfMeasurement=i->second;
unitOfMeasurement=new UnitOfMeasurement;
unitOfMeasurement->setCode(_unitOfMeasurement->code);
unitOfMeasurement->setTitle(*(_unitOfMeasurement->title));
delete _unitOfMeasurement;
return unitOfMeasurement;
}
abc::IUnitOfMeasurement *UnitOfMeasurementManager::getUnitOfMeasurementByTitle(string &title) throw(BLException)
{
BLException blException;
string *t=new string(title);
if(t->length()==0)
{
blException.setGenericException("Title required, length is zero");
throw blException;
}
if(t->length()>50)
{
blException.setGenericException("Title length cannot exceeed 50");
throw blException;
}
map<string *, _UnitOfMeasurement *, UnitOfMeasurementTitleComparator>::iterator i;
i=dataModel.titleWiseMap.find(t);
if(i==dataModel.titleWiseMap.end())
{
blException.setGenericException(string("Invalid unit of measurement title"));
throw blException;
}
abc::IUnitOfMeasurement *unitOfMeasurement;
_UnitOfMeasurement *_unitOfMeasurement;
_unitOfMeasurement=i->second;
unitOfMeasurement=new UnitOfMeasurement;
unitOfMeasurement->setCode(_unitOfMeasurement->code);
unitOfMeasurement->setTitle(*(_unitOfMeasurement->title));
delete _unitOfMeasurement;
delete t;
return unitOfMeasurement;
}
forward_list<abc::IUnitOfMeasurement *> *UnitOfMeasurementManager::getUnitOfMeasurements() throw(BLException)
{
map<string *, _UnitOfMeasurement *>::iterator i=dataModel.titleWiseMap.begin();
_UnitOfMeasurement *unitOfMeasurement;
abc::IUnitOfMeasurement *blUnitOfMeasurement;
forward_list<abc::IUnitOfMeasurement *> *unitOfMeasurements;
unitOfMeasurements=new forward_list<abc::IUnitOfMeasurement *>;
forward_list<abc::IUnitOfMeasurement *>::iterator listi=unitOfMeasurements->before_begin();
while(i!=dataModel.titleWiseMap.end())
{
unitOfMeasurement=i->second;
blUnitOfMeasurement=new UnitOfMeasurement;
blUnitOfMeasurement->setCode(unitOfMeasurement->code);
blUnitOfMeasurement->setTitle(*(unitOfMeasurement->title));
listi=unitOfMeasurements->insert_after(listi,blUnitOfMeasurement);
++i;
}
return unitOfMeasurements;
}
int UnitOfMeasurementManager::UnitOfMeasurementCodeExists(int code) throw(BLException)
{
if(code<=0)
{
return false;
}
map<int, _UnitOfMeasurement *>::iterator i;
i=dataModel.codeWiseMap.find(code);
if(i->first==code)
{
return true;
}
return false;
}
int UnitOfMeasurementManager::UnitOfMeasurementTitleExists(string &title) throw(BLException)
{
string *t=new string(title);
if(t->length()==0)
{
return false;
}
if(t->length()>50)
{
return false;
}
map<string *, _UnitOfMeasurement *, UnitOfMeasurementTitleComparator>::iterator i;
i=dataModel.titleWiseMap.find(t);
if(i==dataModel.titleWiseMap.end())
{
delete t;
return false;
}
delete t;
return true;
}
int UnitOfMeasurementManager::UnitOfMeasurementCount() throw(BLException)
{
return dataModel.codeWiseMap.size();
}
