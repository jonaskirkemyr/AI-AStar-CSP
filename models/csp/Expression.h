#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <iostream>
using namespace std;

class Expression
{
	private:
		static int numb;
		const int id;
	public:
		Expression();
		~Expression();

		const int getID() const;

		bool operator==(const Expression&) const;

};

#endif
