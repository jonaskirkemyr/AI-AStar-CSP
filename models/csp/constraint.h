#ifndef CONSTRAINT_H
#define CONSTRAINT_H
 
#include <unordered_map>
#include <list>
#include "reviseNode.h"
#include "Expression.h"
#include "../../exprtk/exprtk.hpp"
#include <vector>
#include "domain.h"


#include <iostream>
#include <map>
using namespace std;

template <class T>
class Constraint
{
	private:
		string strC;//the math expression

		//unordered_map<string,vector<T>*> variables;//variables in expression (like 'x', 'y', etc.)

		unordered_map<string, Domain *> variables;

		bool loopDomain(vector<string>&,int,exprtk::expression<T>&,map<string,T>*);


	public:
		Constraint();
		Constraint(const string &);
		Constraint(const Constraint&);
		~Constraint();

		void setConstraint(const string&);
		const string& getConstraint() const; 

		//void addVariable(const string&,vector<T>*);
		void addVariable(const string&, Domain*);

		Domain * getDomain(const string&); 
		bool isInDomain(const string&,T,bool=false);//variable, value, del
		bool posInDomain(const string&,int);//variable,pos

		bool isExprInDomain(Expression*);

		const string& setDomain(Domain *);


		//void getSizeDomains(int*&,int&);


		void fillQueue(list<ReviseNode<T>*>&,int);
		void fillQueue(list<ReviseNode<T>*>*);


		bool checkSatisfaction(const string&, T);

		bool removeFromDomain(const string&,T);

		void printDomains();

		bool setValueVar(const string&,T);

		const unordered_map<string,Domain*> &getAllVariables() const; 

		string * getVariables();
		size_t getSize();

		size_t getNumberInDomain();
		 


};
#include "constraint.cpp"

#endif
