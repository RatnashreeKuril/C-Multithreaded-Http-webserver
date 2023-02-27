#include<iostream>
#include<dl/uom>
#include<dl/uomdao>
using namespace inventory;
using namespace data_layer;
int main()
{
UnitOfMeasurementDAO unitOfMeasurementDAO;
cout<<"Number of records in context unit of measurement : "<<unitOfMeasurementDAO.getCount();
return 0;
}