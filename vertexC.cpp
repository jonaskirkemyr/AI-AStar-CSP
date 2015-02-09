#include "vertexC.h"


void VertexC::initValues()
{
	for(int i=0;i<k;++i)
		domainValues.push_back(i);
}

void VertexC::initConstraint()
{
	for(int i=0;i<vertex;++i)
	{
		domains[i].setDomain(&domainValues);
		domains[i].setParent(&expression[i]);

		
	}

	for(int i=0;i<edges;++i)
		constraints[i].setConstraint("x!=y");
}


void VertexC::delAll()
{
	delete agac;

	delete domains;
	delete expression;
	delete constraints;

	agac=nullptr;
	domains=nullptr;
	expression=nullptr;
	constraints=nullptr;

	domainValues.clear();
}

void VertexC::reset()
{
	domains=new Domain[this->vertex];
	expression=new Expression[this->vertex];
	constraints=new Constraint<double>[this->edges];

	cSize=0;
	agac=new AGac<double>(this->edges);

	initValues();
	initConstraint();
}



VertexC::VertexC(int k,int v,int e)
{
	this->k=k;
	this->vertex=v;
	this->edges=e;

	
	reset();
}

VertexC::~VertexC()
{
	delAll();
}


int VertexC::getK()
{
	return k;
}

int VertexC::getNumbVertex()
{
	return vertex;
}

int VertexC::getEdges()
{
	return edges;
}

void VertexC::setK(int i)
{
	k=i;
	delAll();
	reset();

}

void VertexC::setNumbVertex(int i)
{
	vertex=i;
}

void VertexC::setEdges(int i)
{
	edges=i;
}





void VertexC::setVariables(int a,int b)
{
	constraints[cSize].addVariable("x",&domains[a]);
	constraints[cSize].addVariable("y",&domains[b]);

	++cSize;
}

bool VertexC::isAllSet()
{
	for(int i=0;i<cSize;++i)
		if(constraints[i].getSize()!=2)
			return false;
	return true;
}

bool VertexC::registerConstraint()
{
	if(!isAllSet())return false;

	for(int i=0;i<cSize;++i)
		agac->addConstraint(&constraints[i]);

	return true;
}

void VertexC::run()
{
	if(!isAllSet())return;

	agac->init();
}