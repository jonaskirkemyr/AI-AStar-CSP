/*
                                                     dddddddd
NNNNNNNN        NNNNNNNN                             d::::::d
N:::::::N       N::::::N                             d::::::d
N::::::::N      N::::::N                             d::::::d
N:::::::::N     N::::::N                             d:::::d
N::::::::::N    N::::::N   ooooooooooo       ddddddddd:::::d     eeeeeeeeeeee
N:::::::::::N   N::::::N oo:::::::::::oo   dd::::::::::::::d   ee::::::::::::ee
N:::::::N::::N  N::::::No:::::::::::::::o d::::::::::::::::d  e::::::eeeee:::::ee
N::::::N N::::N N::::::No:::::ooooo:::::od:::::::ddddd:::::d e::::::e     e:::::e
N::::::N  N::::N:::::::No::::o     o::::od::::::d    d:::::d e:::::::eeeee::::::e
N::::::N   N:::::::::::No::::o     o::::od:::::d     d:::::d e:::::::::::::::::e
N::::::N    N::::::::::No::::o     o::::od:::::d     d:::::d e::::::eeeeeeeeeee
N::::::N     N:::::::::No::::o     o::::od:::::d     d:::::d e:::::::e
N::::::N      N::::::::No:::::ooooo:::::od::::::ddddd::::::dde::::::::e
N::::::N       N:::::::No:::::::::::::::o d:::::::::::::::::d e::::::::eeeeeeee
N::::::N        N::::::N oo:::::::::::oo   d:::::::::ddd::::d  ee:::::::::::::e
NNNNNNNN         NNNNNNN   ooooooooooo      ddddddddd   ddddd    eeeeeeeeeeeeee


*/

#ifndef NODE_H
#define NODE_H



#include "../settings/settings.h"
#include <vector>
class Node
{
	private:
		int id;

		float heuristic;
		float g_value;
		float f_value;

		float computeF();

		

		Node *parent;
		vector<Node *>children;

		void copy(const Node&);

	protected:
		void setID(int);//don't want to change id of node when first set

	public:
		Node(int=Settings::NOT_INIT);//where NOT_INIT is not initialized value for id
		Node(int,int,int);//id, g_value,heuristic
		Node(const Node&);

		virtual void setGValue(float);
		virtual void setHeuristic(float);

		virtual float getGValue();
		virtual float getHeuristic();
		virtual float getFValue() const;

		virtual int getID();

		virtual void addChild(Node *);
		virtual Node * getChild(size_t) const;

		virtual size_t getChildSize() const;

		virtual void setParent(Node*);
		virtual Node * getParent() const;


		//operators
		virtual bool operator==(const Node&) const;
		bool operator!=(const Node&) const;
		bool operator<(const Node&)const;
		bool operator>(const Node&)const;
		Node & operator=(const Node&);





};


#endif


 