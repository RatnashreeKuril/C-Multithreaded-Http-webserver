#include<iostream>
#include<dl/uom>
#include<dl/iuom>
#include<dl/uomdao>
using namespace inventory;
using namespace data_layer;
int main()
{
int code;
cout<<"Enter code : ";
cin>>code;
UnitOfMeasurementDAO unitOfMeasurementDAO;
abc::IUnitOfMeasurement *unitOfMeasurement;
try
{
unitOfMeasurement=unitOfMeasurementDAO.getByCode(code);
cout<<"Code : "<<unitOfMeasurement->getCode()<<", Title : "<<unitOfMeasurement->getTitle();
}catch(DAOException daoException)
{
cout<<daoException.what();
}
return 0;
}