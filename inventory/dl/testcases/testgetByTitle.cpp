#include<iostream>
#include<dl/uom>
#include<dl/iuom>
#include<dl/uomdao>
using namespace inventory;
using namespace data_layer;
int main()
{
string title;
cout<<"Enter title : ";
cin>>title;
UnitOfMeasurementDAO unitOfMeasurementDAO;
abc::IUnitOfMeasurement *unitOfMeasurement;
try
{
unitOfMeasurement=unitOfMeasurementDAO.getByTitle(title);
cout<<"Code : "<<unitOfMeasurement->getCode()<<", Title : "<<unitOfMeasurement->getTitle();
}catch(DAOException daoException)
{
cout<<daoException.what();
}
return 0;
}