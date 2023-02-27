#include<iostream>
#include<dl/uom>
#include<dl/uomdao>
#include<dl/iuom>
using namespace inventory;
using namespace data_layer;
int main()
{
string title("abcd");
UnitOfMeasurementDAO unitOfMeasurementDAO;
if(unitOfMeasurementDAO.titleExists(title))
{
cout<<title<<" exist.";
}
else
{
cout<<title<<" dose not exist.";
}
return 0;
}