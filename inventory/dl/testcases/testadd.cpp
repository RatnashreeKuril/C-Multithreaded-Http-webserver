#include<iostream>
#include<dl/uom>
#include<dl/uomdao>
using namespace inventory;
using namespace data_layer;
int main()
{
UnitOfMeasurement m;
UnitOfMeasurementDAO unitOfMeasurementDAO;
string title;
cout<<"Enter title : ";
cin>>title;
m.setTitle(title);
try
{
unitOfMeasurementDAO.add(&m);
cout<<"Unit of measurement added with code as : "<<m.getCode();
}catch(DAOException daoException)
{
cout<<daoException.what();
}
return 0;
}