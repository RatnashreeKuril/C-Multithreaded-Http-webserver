#include<iostream>
#include<dl/uom>
#include<dl/uomdao>
using namespace inventory;
using namespace data_layer;
int main()
{
string title;
cout<<"Enter title : ";
cin>>title;
UnitOfMeasurementDAO unitOfMeasurementDAO;
if(unitOfMeasurementDAO.titleExists(title)) cout<<title<<" exists.";
else cout<<title<<" does not exists.";
return 0;
}