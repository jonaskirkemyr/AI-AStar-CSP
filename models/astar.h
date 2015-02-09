/*

               AAA
              A:::A
             A:::::A
            A:::::::A          ******         ******
           A:::::::::A         *:::::*       *:::::*
          A:::::A:::::A        ***::::*******::::***
         A:::::A A:::::A          **:::::::::::**
        A:::::A   A:::::A      ******:::::::::******
       A:::::A     A:::::A     *:::::::::::::::::::*
      A:::::AAAAAAAAA:::::A    ******:::::::::******
     A:::::::::::::::::::::A      **:::::::::::**
    A:::::AAAAAAAAAAAAA:::::A  ***::::*******::::***
   A:::::A             A:::::A *:::::*       *:::::*
  A:::::A               A:::::A******         ******
 A:::::A                 A:::::A
AAAAAAA                   AAAAAAA



 */


#ifndef ASTAR_H
#define ASTAR_H


#include "node.h"
#include "notify.h"

#include "../settings/functions.h"
#include <queue>
#include <unordered_map>
#include <vector>
#include <list>
using namespace std;

class Astar : public Notify
{ 
	private:
		//vector<Node*>closed;
		//already evaluated nodes (the hash table) (int = id of node, Node* pointer to node for accessing obj)
		//Node **closed;

		int numbNodes;

		unordered_map<int,Node*>closed;//closed nodes
		//priority_queue<Node*,vector<Node*>,Functions::compNodes>opened;//nodes to be evaluated
		list<Node*> opened;

		string type;//astar,bfs,dfs

		Node * root;//start search
		Node * goal;//goal node

		Node * current;//current node being popped from open set

		//Node * getLowestNode();//returns best node to process



		void sortList();

		Node * moveToClosed();

		void attachAndEvaluate(Node*,Node*);//child,parent
		void pathImprove(Node*);

		void setCurrent(Node*);


		 
	protected:
		unordered_map<int,Node*>nodes;//node created, and pos of it (id)


		Node * checkIfExists(Node*);//checks if a node is already in var 'nodes'

		void setStart(Node*);
		void setGoal(Node*);

		virtual void addToOpen(Node*);

		virtual float arcCost(Node*,Node*)=0;//NEEDS TO BE IMPLEMENTED - computes arc cost of moving from node a -> b
		virtual void computeHeuristic(Node*)=0;//NEEDS TO BE IMPLEMENTED - computes heuristic for Node
		virtual void generateNeighbours(int,vector<Node*>&)=0;//NEEDS TO BE IMPLEMENTED - generates the neighours of node at pos int
		virtual void loopNeighbours(Node*,vector<Node*>&);//loops through the neighbours/children for the node*


		virtual void addNeighboursToNodes(vector<Node*>&);

		void clearAll();

		Astar();//can't create this object, needs to be inherited

	public:

		virtual ~Astar();

		Node * getStart() const;
		Node * getGoal() const;

		Node * run();

		void initStart();
		int runOnce();

		Node * getCurrent() const;


		void printOpenList();

		void setType(const string&);
		const string &getType() const;

		int getNumbCreated();


};




#endif
