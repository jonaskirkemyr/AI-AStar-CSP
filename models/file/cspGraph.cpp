#include "cspGraph.h"

CSPGraph::CSPGraph()
{
	coordinates=nullptr;
	connections=nullptr;
	conSize=0;
	cordSize=0;

}

CSPGraph::CSPGraph(const CSPGraph& copy)
{
	coordinates=new float*[copy.NV];
	for(int i=0;i<copy.NV;++i)
		coordinates[i]=new float[2];

	connections=new int*[copy.NE-1];
	for(int i=0;i<(copy.NE);++i)
		connections[i]=new int[2];

	NV=copy.NV;
	NE=copy.NE;

	cordSize=copy.cordSize;
	conSize=copy.conSize;

	for(int i=0;i<cordSize;++i)
	{
		coordinates[i][0]=copy.coordinates[i][0];
		coordinates[i][1]=copy.coordinates[i][1];
	}

	for(int i=0;i<conSize;++i)
	{
		connections[i][0]=copy.connections[i][0];
		connections[i][1]=copy.connections[i][1];
	}
}

void CSPGraph::setNV(int n)
{
	NV=n;
}

void CSPGraph::setNE(int n)
{
	NE=n;
}

void CSPGraph::initArrays()
{
	coordinates=new float*[NV];
	for(int i=0;i<NV;++i)
		coordinates[i]=new float[2];

	connections=new int*[NE];
	for(int i=0;i<NE;++i)
		connections[i]=new int[2];
}

void CSPGraph::addCoordinate(float x,float y)
{
	if(cordSize>=NV)return;

	coordinates[cordSize][0]=x;
	coordinates[cordSize][1]=y;

	++cordSize;
}

void CSPGraph::addConnections(int a,int b)
{
	if(conSize>=(NE))return;

	connections[conSize][0]=a;
	connections[conSize][1]=b;

	++conSize;
}


float * CSPGraph::getCoordinatesAt(int i)
{
	if(i<0 || i>cordSize)
		return nullptr;
	return coordinates[i];
}

int * CSPGraph::getConnectionAt(int i)
{
	if(i<0 || i>conSize)
		return nullptr;
	return connections[i];
}

int CSPGraph::getConSize()
{
	return conSize;
}

int CSPGraph::getCordSize()
{
	return cordSize;
}

int CSPGraph::getNV()
{
	return NV;
}


int CSPGraph::getNE()
{
	return NE;
}


