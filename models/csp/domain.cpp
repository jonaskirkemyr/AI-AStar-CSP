#include "domain.h"

Domain::Domain()
{
	parent=nullptr;
	varDomain=nullptr;
}

Domain::Domain(const Domain & copy)
{
	//cout<<"COPY DOMAIN";
	parent=copy.parent;
	varDomain=new vector<double>;

	for(size_t i=0;i<copy.getDomain()->size();++i)
		varDomain->push_back(copy.getDomain()->at(i));
}

Domain::~Domain()
{
	cout<<"deleting\n";
	if(parent!=nullptr)
	{
		delete parent;
		//parent=nullptr;
	}
	if(varDomain!=nullptr)
	{
		delete varDomain;
		//varDomain=nullptr;
	}
	cout<<"end delete\n";
}

void Domain::setParent(Expression *e)
{
	parent=e;
}

void Domain::setDomain(vector<double>* d)
{
	varDomain=new vector<double>;

	for(size_t i=0;i<d->size();++i)
		varDomain->push_back(d->at(i));
	//varDomain=d;
}

Expression *Domain::getParent() const
{
	return parent;
}

vector<double> *Domain::getDomain() const
{
	return varDomain;
}