#ifndef CSPGRAPH_H
#define CSPGRAPH_H

class CSPGraph
{
	private:
		int NV;
		int NE;

		float **coordinates;//[2]
		int cordSize;

		int **connections;//[2]
		int conSize;

	
	public:
		CSPGraph();
		CSPGraph(const CSPGraph&);

		void setNV(int);
		void setNE(int);

		void initArrays();

		void addCoordinate(float,float);
		void addConnections(int,int);


		float *getCoordinatesAt(int);
		int * getConnectionAt(int);

		int getConSize();
		int getCordSize();

		int getNV();
		int getNE();

};

#endif