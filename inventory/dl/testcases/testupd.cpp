#include<iostream>
#include<dl/uom>
#include<dl/uomdao>
using namespace inventory;
using namespace data_layer;
int main()
{
int code;
string title;
cout<<"Enter code : ";
cin>>code;
cout<<"Enter title : ";
cin>>title;
UnitOfMeasurement m;
UnitOfMeasurementDAO unitOfMeasurementDAO;
m.setCode(code);
m.setTitle(title);
try
{
unitOfMeasurementDAO.update(&m);
cout<<"Unit of measurement updated";
}catch(DAOException daoException)
{
cout<<daoException.what();
}
return 0;
}