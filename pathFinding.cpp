#include "pathFinding.h"


/**
.#####...#####...######..##..##...####...######..######.
.##..##..##..##....##....##..##..##..##....##....##.....
.#####...#####.....##....##..##..######....##....####...
.##......##..##....##.....####...##..##....##....##.....
.##......##..##..######....##....##..##....##....######.
........................................................
**/

void PathF::init_map(int w,int h)
{
	width_board=w;
	height_board=h;


	//allocate memory for map
	map=new int*[height_board];

	for(int i=0;i<height_board;++i)
		map[i]=new int[width_board];

	for(int i=0;i<height_board;++i)
		for(int j=0;j<width_board;++j)
			map[i][j]=Settings::NOT_INIT;//not initialized
}




/**
 * Loads map to be used in pathfinding
 *
 * Loops through input map, and copies
 * values over to local map variable
 *
 * when goal/start position is found
 * the nodes is pushed into the nodes vector
 * and set as start&goal in Astar obj.
 * The int value is set as the position
 * in the array (1-dimensional value!)
 *
 *
 * codes for the map is defined in pathFinding.h
 * @param map representation of map
 */
void PathF::loadMap(int ** map)
{

	clearAll();


	for(int i=0;i<height_board;++i)
	{
		for(int j=0;j<width_board;++j)
		{
			this->map[i][j]=map[i][j];

			if(this->map[i][j]==Settings::START_POS)//if start position
			{
				int tempID=i*height_board+j;//position of node
				startPos=tempID;
				Node *start=new Node(tempID);
				nodes.emplace(tempID,start);
				setStart(start);

			}
			else if(this->map[i][j]==Settings::GOAL_POS)//if goal position
			{
				int tempID=i*height_board+j;//position of node
				goalPos=tempID;
				Node *goal=new Node(tempID);
				//nodes.emplace(tempID,goal);
				setGoal(goal);
			}
		}
	}
}




/*
.#####...#####....####...######..######...####...######..######..#####..
.##..##..##..##..##..##....##....##......##..##....##....##......##..##.
.#####...#####...##..##....##....####....##........##....####....##..##.
.##......##..##..##..##....##....##......##..##....##....##......##..##.
.##......##..##...####.....##....######...####.....##....######..#####..
........................................................................
*/

float PathF::arcCost(Node* a,Node * b)//really just 1
{
	int columnA=getColumnFromPos(a->getID());
	int rowA=getRowFromPos(a->getID());

	int columnB=getColumnFromPos(b->getID());
	int rowB=getRowFromPos(b->getID());

	float sum=abs(columnA-columnB)+abs(rowA-rowB);//manhatten distance

	//return sum*Settings::COST_MOVE;//where sum is amount of moves needed to move from a->b, and cost_move is cost pr move made
	//cout<<"SUM "<<sum<<endl;
	return sum;
	//return 0.2;
	//return 10;
	//return 1;
}


void PathF::computeHeuristic(Node* n)
{
	//n->setHeuristic(arcCost(n,getGoal())/Settings::COST_MOVE);
	//return arcCost(n,getGoal());
	//
	int columnA=getColumnFromPos(n->getID());
	int rowA=getRowFromPos(n->getID());

	int columnB=getColumnFromPos(getGoal()->getID());
	int rowB=getRowFromPos(getGoal()->getID());

	float sum=abs(columnA-columnB)+abs(rowA-rowB);//manhatten distance

	n->setHeuristic(sum);
}






void PathF::generateNeighbours(int pos,vector<Node*>& childs)
{

	//vector<Node *>tempChildren;

	//children position
	int left_child=pos-1;
	int right_child=pos+1;

	int top_child=pos-width_board;
	int down_child=pos+width_board;

	/*cout<<"pos:"<<pos<<endl;
	cout<<"top:"<<top_child<<endl;
	cout<<"down:"<<down_child<<endl;
	cout<<"left:"<<left_child<<endl;
	cout<<"right:"<<right_child<<endl<<endl;*/

	/**LEFT**/
	if(left_child>=0 && pos%width_board!=0)//pos%width_board==0 only when in first pos in row
	{
		if(map[getColumnFromPos(left_child)][getRowFromPos(left_child)]!=Settings::OBSTACLE)
		{
			Node* temp=new Node(left_child);//generates new node and put it in generated nodes (hash table)
			childs.push_back(temp);
		}
	}

	/**RIGHT**/
	if(right_child%width_board!=0)//pos%width_board==0 only when in first pos in row
	{
		if(map[getColumnFromPos(right_child)][getRowFromPos(right_child)]!=Settings::OBSTACLE)
		{
			Node* temp=new Node(right_child);//generates new node and put it in generated nodes (hash table)
			childs.push_back(temp);
		}
	}

	/**TOP**/
	if(top_child>=0)
	{
		if(map[getColumnFromPos(top_child)][getRowFromPos(top_child)]!=Settings::OBSTACLE)
		{
			Node* temp=new Node(top_child);//generates new node and put it in generated nodes (hash table)
			childs.push_back(temp);
		}
	}

	/**DOWN**/
	if(down_child<(width_board*height_board))
	{
		/*cout<<"POS"<<pos<<endl;

		cout<<"DOWN CHILD:"<<down_child<<" "<<map[getColumnFromPos(down_child)][getRowFromPos(down_child)]<<endl;
		cout<<"COL:"<<getColumnFromPos(down_child)<<" ROW:"<<getRowFromPos(down_child)<<endl;*/
		if(map[getColumnFromPos(down_child)][getRowFromPos(down_child)]!=Settings::OBSTACLE)
		{
			//cout<<"NOT OBSTACLE\n"<<Settings::OBSTACLE<<endl;
			Node* temp=new Node(down_child);//generates new node and put it in generated nodes (hash table)
			childs.push_back(temp);
		}
		//cout<<endl;
	}

	//return tempChildren;

}




/**
.#####...##..##..#####...##......######...####..
.##..##..##..##..##..##..##........##....##..##.
.#####...##..##..#####...##........##....##.....
.##......##..##..##..##..##........##....##..##.
.##.......####...#####...######..######...####..
................................................
**/

PathF::PathF()
{
	map=nullptr;
}

PathF::PathF(int w,int h)
{
	init_map(w,h);
}

PathF::PathF(int **map,int w,int h)
{
	init_map(w,h);
	loadMap(map);
}

PathF::PathF(const PathF& copy)
{
	init_map(copy.width_board,copy.height_board);

	for(int i=0;i<height_board;++i)
		for(int j=0;j<width_board;++j)
			map[i][j]=copy.map[i][j];

}

PathF::~PathF()
{
	/*for(int i=0;i<height_board;++i)
		delete[] nodes[i];
	delete[] nodes;
	nodes=nullptr;*/
	//cout<<"delete path\n";
	//free zhe memory
	for(int i=0;i<height_board;++i)
		delete[] map[i];
	delete[] map;
	map=nullptr;//make sure map doesn't point to anything
	//cout<<"end delete path\n";
}




void PathF::setMap(int ** tempMap)
{
	init_map(width_board,height_board);
	loadMap(tempMap);
}



int PathF::getWidth() const
{
	return width_board;
}

int PathF::getHeight() const
{
	return height_board;
}

void PathF::setWidth(int w)
{
	width_board=w;
}

void PathF::setHeight(int h)
{
	height_board=h;
}

int ** PathF::getMap()
{
	return map;
}




int PathF::getColumnFromPos(int i)//compute first [] in 2d array
{
	//return i%height_board;
	return ceil(i/width_board);
}

int PathF::getRowFromPos(int i)//compute second [] in 2d array
{
	//return ceil(i/width_board);
	return i%height_board;


}




void PathF::printMap()
{
	for(int i=0;i<height_board;++i)
	{
		for(int j=0;j<width_board;++j)
			cout<<map[i][j]<<" ";
		cout<<endl;
	}
}


