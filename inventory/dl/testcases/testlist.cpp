#include<iostream>
#include<dl/uom>
#include<dl/iuom>
#include<forward_list>
#include<dl/uomdao>
using namespace inventory;
using namespace data_layer;
int main()
{
forward_list<abc::IUnitOfMeasurement *>*list;
UnitOfMeasurementDAO unitOfMeasurementDAO;
try
{
list=unitOfMeasurementDAO.getAll();
forward_list<abc::IUnitOfMeasurement *>::iterator i;
abc::IUnitOfMeasurement * unitOfMeasurement;
for(i=list->begin();i!=list->end();++i)
{
unitOfMeasurement=*i;
cout<<"Code : "<<unitOfMeasurement->getCode()<<", Title : "<<unitOfMeasurement->getTitle()<<endl;
}
}catch(DAOException daoException)
{
cout<<daoException.what();
}
return 0;
}