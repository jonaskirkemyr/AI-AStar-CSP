#ifndef ASTARCSP_H
#define ASTARCSP_H

#include "../astar.h"
#include "constraint.h"
//#include "domain.h"
#include "searchState.h"
#include "csp.h"

#include <stdlib.h>
#include <time.h>

class AstarCSP : public Astar
{
	private:
		//Constraint<int> * constraints;
		//Domain * domains;
		vector<Constraint<double>* > constraints;
		CSP<double> *csp;

		SearchState * states;
		int size;
		int maxSize;


	protected:
		virtual float arcCost(Node*,Node*);//computes arc cost of moving from node a -> b
		virtual void computeHeuristic(Node*);//computes heuristic for Node
		virtual void generateNeighbours(int,vector<Node*>&);//generates the neighours of node at pos int


	public:
		AstarCSP();
		AstarCSP(const AstarCSP&);

		void init(SearchState*);//start state, will generate goal state inside function

		void addPtrC(Constraint<double>*,int);//constraints and size of array, adds pointer to the constraints used in csp
		void addPtrCsp(CSP<double>*);//csp ptr used by astar


};

#endif