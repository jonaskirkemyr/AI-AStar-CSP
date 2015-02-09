#include "node.h"

/**
.#####...#####...######..##..##...####...######..######.
.##..##..##..##....##....##..##..##..##....##....##.....
.#####...#####.....##....##..##..######....##....####...
.##......##..##....##.....####...##..##....##....##.....
.##......##..##..######....##....##..##....##....######.
........................................................
**/

void Node::setID(int id)
{
	this->id=id;
}


void Node::copy(const Node& copy)
{
	id=copy.id;
	heuristic=copy.heuristic;
	g_value=copy.g_value;

	parent=new Node();
	parent=copy.parent;
}

float Node::computeF()
{
	f_value=heuristic+g_value;
	return heuristic+g_value;
}


/**
.#####...##..##..#####...##......######...####..
.##..##..##..##..##..##..##........##....##..##.
.#####...##..##..#####...##........##....##.....
.##......##..##..##..##..##........##....##..##.
.##.......####...#####...######..######...####..
................................................
**/

Node::Node(int id)
{
	setID(id);

	parent=nullptr;
	heuristic=Settings::NOT_INIT;
	g_value=Settings::NOT_INIT;
}

Node::Node(const Node &copy)
{
	this->copy(copy);//calls copy function, to copy from obj to this (obj)
}

Node::Node(int id,int g, int h)
{
	setID(id);
	heuristic=(float)h;
	g_value=(float)g;
}

void Node::setGValue(float g)
{
	//cout<<"set g value "<<getID()<<endl;
	g_value=g;
	computeF();
}

void Node::setHeuristic(float h)
{
	//cout<<"set h value "<<getID()<<endl;
	heuristic=h;
	computeF();
}

float Node::getGValue()
{
	return g_value;
}

float Node::getHeuristic()
{
	return heuristic;
}

float Node::getFValue() const
{
	//if(heuristic==Settings::NOT_INIT || g_value==Settings::NOT_INIT)//check if g_value & heuristic is actually set
	//	return Settings::NOT_INIT;
	return f_value;
}

int Node::getID()
{
	return id;
}

void Node::addChild(Node * add)
{
	children.push_back(add);
}

Node * Node::getChild(size_t i) const
{
	if(i>=0 && i<getChildSize())
		return children.at(i);
	return nullptr;
}

size_t Node::getChildSize() const
{
	return children.size();
}


void Node::setParent(Node* parent)
{
	this->parent=parent;
}

Node * Node::getParent() const
{
	return parent;
}



/**OPERATOR OVERLOADING**/
bool Node::operator==(const Node& right) const
{
	return id==right.id;
}

bool Node::operator!=(const Node &right) const
{
	return !(*this==right);
}

bool Node::operator<(const Node&right) const
{
	//cout<<"\n\noperator< \n\n";
	if(getFValue()==right.getFValue())
		return id<right.id;
	return getFValue()<right.getFValue();
}

bool Node::operator>(const Node&right)const
{
	return getFValue()>right.getFValue();
}

Node& Node::operator=(const Node &right)
{
	if(this==&right)//if same object
		return *this;

	delete parent;//delete & free memory
	parent=nullptr;

	copy(right);//copy obj to this

	return *this;
}
