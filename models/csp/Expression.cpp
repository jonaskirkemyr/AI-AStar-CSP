#include "Expression.h"

Expression::Expression() : id(numb++)
{

}

Expression::~Expression()
{
	cout<<"delete expr";
}

const int Expression::getID() const
{
	return id;
}




/**OPERATOR OVERLOADING**/
bool Expression::operator==(const Expression& right) const
{
	//cout<<"operator==\n";
	return getID()==right.getID();
}

int Expression::numb=0;//start at pos 0