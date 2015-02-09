#ifndef REVISENODE_H
#define REVISENODE_H

template <class T>
class Constraint;

template <class T>
class ReviseNode
{
	private:
		string variable;
		Constraint<T> *constraint;
	

	public:
		ReviseNode(string,Constraint<T>&);
		ReviseNode(string);
		~ReviseNode();
		 
		const string &getVariable() const;
		Constraint<T> * getConstraint() const; 
};

#include "reviseNode.cpp"
#endif