#ifndef SEARCHSTATE_H
#define SEARCHSTATE_H

#include "domain.h"
#include <stdlib.h>
#include <time.h>
#include "../node.h"
#include "../../settings/settings.h"

#include <iostream>
#include <limits>
using namespace std;

class SearchState : public Node
{

	private:
		//Domain *domain;
		vector<Domain*> domain;
		int size;
		int maxSize;

		int posA;//position in domain array assumed
		double posV;//value assumed in domain vector

		void increaseD();

		bool isGoal;

		static int incrID; 

	public: 
		SearchState(int,int=numeric_limits<int>::max());
		SearchState(bool);
		SearchState(const SearchState&);

		bool addDomain(Domain *);

		int getSize();
		Domain * getDomainAt(int=0);

		int guess(int=0);
		bool guessValue(size_t,int);

		int getPosA();
		double getPosV();

		size_t getNumberInDomain();
		double getSumDomain();

		int smallestDomain();

		virtual bool operator==(const Node&) const;
		virtual bool operator==(const SearchState&) const; 
		SearchState & operator=(const SearchState&);

		size_t getSizeAt(int);

		void printAll();

		virtual void setHeuristic(float);



}; 

#endif