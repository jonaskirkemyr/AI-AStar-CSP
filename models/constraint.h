#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include <unordered_map>
#include <list>
#include "reviseNode.h"
#include <vector>

#include "../exprtk/exprtk.hpp"

#include <iostream>
#include <map>
using namespace std;

template <class T>
class Constraint
{
	private:
		string strC;//the math expression

		unordered_map<string,vector<T>*> variables;//variables in expression (like 'x', 'y', etc.)

		bool loopDomain(vector<string>&,int,exprtk::expression<T>&,map<string,T>*);


	public:
		Constraint();
		Constraint(const string &);
		Constraint(const Constraint&);
		~Constraint();

		void setConstraint(const string&);
		const string& getConstraint() const; 

		void addVariable(const string&,vector<T>*);

		vector<T> * getDomain(const string&) const; 
		bool isInDomain(const string&,T,bool=false);//variable, value, del
		bool posInDomain(const string&,int);//variable,pos


		//void getSizeDomains(int*&,int&);


		void fillQueue(list<ReviseNode<T>*>&,int);
		void fillQueue(list<ReviseNode<T>*>*);


		bool checkSatisfaction(const string&, T);

		bool removeFromDomain(const string&,T);

		void printDomains();

		bool setValueVar(const string&,T);

		const unordered_map<string,vector<T>*> &getAllVariables() const;

		string * getVariables();
		size_t getSize();
		 


};
#include "constraint.cpp"

#endif
