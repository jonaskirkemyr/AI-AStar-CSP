#include "astar.h"
#include "csp/searchState.h"

#include <iostream>
#include "conio.h"
using namespace std;

/**
.#####...#####...######..##..##...####...######..######.
.##..##..##..##....##....##..##..##..##....##....##.....
.#####...#####.....##....##..##..######....##....####...
.##......##..##....##.....####...##..##....##....##.....
.##......##..##..######....##....##..##....##....######.
........................................................
**/


/**
 * Takes first element in list 'opened'
 * and push it back onto closed
 */
Node * Astar::moveToClosed()
{
	Node *temp=new Node();
	//temp=opened.top();//copies node to temp node before removing
	
	temp=opened.front();
	//opened.pop();

	opened.pop_front();
	//cout<<"moving ---"<<temp->getID()<<"--- from open to closed\n";


	//closed.emplace(temp->getID(),temp);
	closed[temp->getID()]=temp;

	//cout<<"closed is now: "<<(closed[temp->getID()])->getID()<<endl;

	return closed[temp->getID()];
	//closed.push_back(temp);

	//closed.emplace(temp->getID(),temp);//push back element from opened node to closed
}


void Astar::attachAndEvaluate(Node * child,Node * parent)
{
	//cout<<"PARENT "<<parent<<endl;
	child->setParent(parent);
	child->setGValue(parent->getGValue()+arcCost(child,parent));
	computeHeuristic(child);
}

void Astar::pathImprove(Node * check)
{
	for(size_t i=0;i<check->getChildSize();++i)//Loop through all the children for the checked node
	{
		Node* temp=check->getChild(i);

		if((check->getGValue()+arcCost(temp,check))<check->getGValue())//if there's a path improvement
		{
			temp->setParent(check);//update node with best parent..
			temp->setGValue(check->getGValue()+arcCost(temp,check));//.. and compute new g value
			pathImprove(temp);
		}
	}
}


void Astar::setCurrent(Node* c)
{
	this->current=c;
	tell();//tells listeners current changed
}


/*
.#####...#####....####...######..######...####...######..######..#####..
.##..##..##..##..##..##....##....##......##..##....##....##......##..##.
.#####...#####...##..##....##....####....##........##....####....##..##.
.##......##..##..##..##....##....##......##..##....##....##......##..##.
.##......##..##...####.....##....######...####.....##....######..#####..
........................................................................
*/

Node * Astar::checkIfExists(Node * check)
{
	if(nodes[check->getID()]!=0)
		return nodes[check->getID()];
	return nullptr;
}


void Astar::setStart(Node* start)
{
	root=start;
}

void Astar::setGoal(Node * goal)
{
	this->goal=goal;
}


void Astar::addToOpen(Node* open)
{

	if(type=="dfs")
		opened.push_front(open);
	else
	{
		opened.push_back(open);
		if(type=="astar")
			opened.sort(Functions::compareLess<Node>);
	}
}


void Astar::loopNeighbours(Node* parent,vector<Node*>& neighbours)
{

	for(size_t i=0;i<neighbours.size();++i)
	{
		++numbNodes;
		Node * S=neighbours.at(i);//get neighbour at pos

		Node *checkNode=checkIfExists(S);//check if node has already been created/generated
		if(checkNode!=nullptr)//if checkNode returns a Node* pointer, the Node has already been created
		{
			//cout<<"ALREADY CREATED!\n";
			S=checkNode;
		}
		else//if node hasn't already been created - it isn't either in open or closed list
		{
			attachAndEvaluate(S,parent);
			addToOpen(S);
		}
		parent->addChild(S);//add child to node

		if((parent->getGValue()+arcCost(S,parent))<S->getGValue())//if a cheapter path to S is found
		{
			//cout<<"\n\n\npath improving..\n\n\n";
			attachAndEvaluate(S,parent);//update g_value and best parent

			if(closed[S->getID()])//if node is already in closed list..
				pathImprove(S);//.. update path for all of S's children
			//cout<<"end path improve\n";
		}

	}
}

void Astar::addNeighboursToNodes(vector<Node*>& neighbours)
{
	for(size_t i=0;i<neighbours.size();++i)
	{
		Node *temp=neighbours.at(i);
		int tempID=temp->getID();

		if(!nodes[tempID])
			nodes[tempID]=temp;
	}


}

void Astar::clearAll()
{
	numbNodes=0;
	if(root)
		delete root;
	if(goal)
		delete goal;
	if(current)
		delete current;

	nodes.clear();
	closed.clear();

	while(opened.size()>0)
        opened.pop_front();
		//opened.pop();

	root=nullptr;
	goal=nullptr;
	current=nullptr;

}


Astar::Astar()//don't want to create astar obj
{
	root=nullptr;
	goal=nullptr;
	current=nullptr;
	type="astar";
	numbNodes=0;
}




/**
.#####...##..##..#####...##......######...####..
.##..##..##..##..##..##..##........##....##..##.
.#####...##..##..#####...##........##....##.....
.##......##..##..##..##..##........##....##..##.
.##.......####...#####...######..######...####..
................................................
**/

Astar::~Astar()
{
	//cout<<" del astar\n";
	delete root;
	delete goal;
	delete current;
	//cout<<"end  del astar\n";
}




Node * Astar::getStart() const
{
	return root;
}

Node * Astar::getGoal() const
{
	return goal;
}

Node * Astar::run()
{
	this->root->setGValue(0);//set start gValue for start node
	this->computeHeuristic(this->root);
	//this->root->setHeuristic(this->computeHeuristic(this->root));//compute heuristic from root to goal

//    addToOpen();
	addToOpen(this->getStart());//add root to open list
	int i=0;

	while(!opened.empty())//run while there's elements in the opened list
	{
		Node *current=moveToClosed();//moves node with lowest f to closed list
		setCurrent(current);

		if(*current==*goal)return current;//returns current if it's goal

		vector<Node *>neighbours;

		generateNeighbours(current->getID(),neighbours);

		loopNeighbours(current,neighbours);

		addNeighboursToNodes(neighbours);
		//printOpenList();

		/*cout<<"\nEND RUN #"<<i<<endl;
		cout<<"SIZE OF OPENED:"<<opened.size()<<endl; 
		cout<<"SIZE OF CLOSED:"<<closed.size()<<endl<<endl<<endl;*/

		//printOpenList();
		//getch();
		++i;
	}

	return nullptr;//retuns nullptr if a solution wasn't found

}

void Astar::initStart()
{
	if(!root || !goal)return;

	this->root->setGValue(0);//set start gValue for start node
	this->computeHeuristic(this->root);//compute heuristic from start to goal
	addToOpen(this->getStart());//add root to open list
}

int Astar::runOnce()
{
	if(!opened.empty())
	{
		Node *current=moveToClosed();//moves node with lowest f to closed list
		setCurrent(current);//node to be drawing


		//cout<<current<<endl;
		//cout<<goal<<endl<<endl;

		if(*current==*goal)return 1;//returns if goal found (true/success)


		vector<Node *>neighbours;

		generateNeighbours(current->getID(),neighbours);

		loopNeighbours(current,neighbours);

		addNeighboursToNodes(neighbours);

		return 0;//returns if one run of algorithm was success, and no goal found
	}
	return -1;//returns if no goal found and no more nodes to be retrieved
}


Node * Astar::getCurrent() const
{
	return this->current;
}


void Astar::printOpenList()
{
	cout<<"-----OPEN LIST-----\n";

	for(unordered_map<int,Node*>::iterator it=closed.begin();it!=closed.end();++it)
	{
		cout<<it->first<<", "<<(it->second)->getFValue()<<endl;

	}
	/*for(std::list<Node*>::iterator it=opened.begin();it!=opened.end();++it)
	{
		Node* temp=*it;
		cout<<temp->getID()<<" "<<temp->getFValue()<<endl;
	}*/
	cout<<"-----END OPEN LIST-----\n";
}



void Astar::setType(const string & t)
{
	type=t;
}

const string &Astar::getType() const
{
	return type;
}

int Astar::getNumbCreated()
{
	return numbNodes;
}

