#ifndef VERTEX_H
#define VERTEX_H

#include "models/csp/domain.h"
#include "models/csp/Expression.h"
#include "models/csp/constraint.h"
#include "models/csp/astarGAC.h"

class VertexC
{
	private:
		int k;//number of possible colors
		int vertex;//number of vertexes (maxSize of domains, etc.)
		int edges;

		Domain *domains;//start domains of each vertex
		Expression *expression;//expression to be doneted with each vertex


		Constraint<double> *constraints;
		int cSize;

		AGac<double> *agac;


		vector<double> domainValues;

		void initValues();
		void initConstraint();


		void delAll();
		void reset();

		
	public:
		VertexC(int=5,int=3,int=3);//#colors,#vertex,#edges
		~VertexC();

		int getK();
		int getNumbVertex();
		int getEdges();

		void setK(int);
		void setNumbVertex(int);
		void setEdges(int);

		Domain *getDomains() const;
		Expression *getExpression() const;

		Constraint<double>* getConstraints() const;

		AGac<double> *getAGAC() const;


		void setVariables(int,int);//constraint,domain,domain
		bool isAllSet();//check if all constraints has variables and domains connected
		bool registerConstraint();//add all constraints to agac obj

		void run();




};

#endif