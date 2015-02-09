#ifndef DOMAIN_H
#define DOMAIN_H

#include "Expression.h"
#include <vector>
#include <iostream>

using namespace std;

class Domain
{
	private:
		Expression *parent;
		vector<double> *varDomain;
	
	public:
		Domain();//set domain expression
		Domain(const Domain&);
		~Domain();

		void setParent(Expression *);
		void setDomain(vector<double>*);

		Expression *getParent() const;

		vector<double> *getDomain() const;




};

#endif