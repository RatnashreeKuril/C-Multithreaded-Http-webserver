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
if(unitOfMeasurementDAO.codeExists(code)) cout<<code<<" exists.";
else cout<<code<<" does not exists.";
return 0;
}