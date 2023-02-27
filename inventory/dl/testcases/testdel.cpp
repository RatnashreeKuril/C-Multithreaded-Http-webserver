#include<iostream>
#include<dl/uom>
#include<dl/uomdao>
using namespace inventory;
using namespace data_layer;
int main()
{
int code;
cout<<"Enter code : ";
cin>>code;
UnitOfMeasurementDAO unitOfMeasurementDAO;
try
{
unitOfMeasurementDAO.remove(code);
cout<<"Removed "<<endl;
}catch(DAOException daoException)
{
cout<<daoException.what();
}
return 0;
}