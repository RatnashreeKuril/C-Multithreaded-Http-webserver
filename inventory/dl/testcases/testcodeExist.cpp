#include<iostream>
#include<uom>
#include<uomdao>
#include<iuom>
using namespace inventory;
using namespace data_layer;
int main()
{
int code;
cout<<"Enter code : ";
cin>>code;
UnitOfMeasurementDAO unitOfMeasurementDAO;
if(unitOfMeasurementDAO.codeExists(code))
{
cout<<code<<" exist.";
}
else
{
cout<<code<<" does not exist.";
}
return 0;
}