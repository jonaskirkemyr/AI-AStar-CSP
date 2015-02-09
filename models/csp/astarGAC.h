#ifndef ASTARGAC_H
#define ASTARGAC_H

//#include "../astar.h"
#include "csp.h"
#include "constraint.h"
#include "searchState.h"
#include "astarCSP.h"

template <class T>
class AGac
{
	private:
		Constraint<T> *constraints;
		int maxSize;
		int size;

		CSP<T> * csp;


		AstarCSP * astar;

		void increaseC();//increases the constraint obj

	public:
		AGac(int=5);


		void addConstraint(Constraint<T>*);//adds constraint obj to array

		void init();

		bool isSolution();

	


		 
};

#include "astargac.cpp"
#endif