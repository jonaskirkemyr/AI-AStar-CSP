 /*

PPPPPPPPPPPPPPPPP                           tttt         hhhhhhh             FFFFFFFFFFFFFFFFFFFFFF
P::::::::::::::::P                       ttt:::t         h:::::h             F::::::::::::::::::::F
P::::::PPPPPP:::::P                      t:::::t         h:::::h             F::::::::::::::::::::F
PP:::::P     P:::::P                     t:::::t         h:::::h             FF::::::FFFFFFFFF::::F
  P::::P     P:::::Paaaaaaaaaaaaa  ttttttt:::::ttttttt    h::::h hhhhh         F:::::F       FFFFFF
  P::::P     P:::::Pa::::::::::::a t:::::::::::::::::t    h::::hh:::::hhh      F:::::F
  P::::PPPPPP:::::P aaaaaaaaa:::::at:::::::::::::::::t    h::::::::::::::hh    F::::::FFFFFFFFFF
  P:::::::::::::PP           a::::atttttt:::::::tttttt    h:::::::hhh::::::h   F:::::::::::::::F
  P::::PPPPPPPPP      aaaaaaa:::::a      t:::::t          h::::::h   h::::::h  F:::::::::::::::F
  P::::P            aa::::::::::::a      t:::::t          h:::::h     h:::::h  F::::::FFFFFFFFFF
  P::::P           a::::aaaa::::::a      t:::::t          h:::::h     h:::::h  F:::::F
  P::::P          a::::a    a:::::a      t:::::t    tttttth:::::h     h:::::h  F:::::F
PP::::::PP        a::::a    a:::::a      t::::::tttt:::::th:::::h     h:::::hFF:::::::FF
P::::::::P        a:::::aaaa::::::a      tt::::::::::::::th:::::h     h:::::hF::::::::FF
P::::::::P         a::::::::::aa:::a       tt:::::::::::tth:::::h     h:::::hF::::::::FF
PPPPPPPPPP          aaaaaaaaaa  aaaa         ttttttttttt  hhhhhhh     hhhhhhhFFFFFFFFFFF

*/

/**
			+------------------------+
			| Status Codes for board |
			+------------------------+
			|                        |
			| -1  -  Not initialized |
			|                        |
			|  0  -  Obstacle        |
			|                        |
			|  1  -  Open/Free       |
			|                        |
			|  2  - Start position   |
			|                        |
			|  3  - Goal position    |
			+-----+------------------+

**/


#include "models/astar.h"
#include <math.h>//CEILS
#include <cmath>
#include <iostream>
using namespace std;
//#include <unordered_map>

#ifndef PATHFINDING_H
#define PATHFINDING_H



class PathF : public Astar
{
	private:
		int width_board;
		int height_board;

		void init_map(int,int);
		void createNodes();

		int startPos;
		int goalPos;


		int **map;

		void loadMap(int**);

		//int getOneDimPos;

		

	protected:

		virtual float arcCost(Node*,Node*);//computes arc cost of moving from node a -> b
		virtual void computeHeuristic(Node*);//computes heuristic for Node
		virtual void generateNeighbours(int,vector<Node*>&);//generates the neighours of node at pos int



	public:
		PathF();
		PathF(int,int);//w,h of map
		PathF(int**,int,int);//map,w,h of map
		PathF(const PathF&);
		virtual ~PathF();


		void setMap(int**);//expects input as 2-dim-array. for codes - see desc at top


		int getWidth() const;
		int getHeight() const;

		void setWidth(int);
		void setHeight(int);

		int ** getMap();



		int getColumnFromPos(int);
		int getRowFromPos(int);

		void printMap();

};


#endif
