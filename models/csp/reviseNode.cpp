#include "reviseNode.h"


/**
.#####...#####...######..##..##...####...######..######.
.##..##..##..##....##....##..##..##..##....##....##.....
.#####...#####.....##....##..##..######....##....####...
.##......##..##....##.....####...##..##....##....##.....
.##......##..##..######....##....##..##....##....######.
........................................................
**/


/**
.#####...##..##..#####...##......######...####..
.##..##..##..##..##..##..##........##....##..##.
.#####...##..##..#####...##........##....##.....
.##......##..##..##..##..##........##....##..##.
.##.......####...#####...######..######...####..
................................................
**/

/*template <class T>
ReviseNode<T>::ReviseNode(string variable,T pv,int pc)
{
	this->variable=variable;
	value=pv;
	//posConstraint=pc;
}*/


template <class T>
ReviseNode<T>::ReviseNode(string variable,Constraint<T>&c)
{
	this->variable=variable;
	constraint=&c;
}

template <class T>
ReviseNode<T>::ReviseNode(string var)
{
	this->variable=var;
}

template <class T>
ReviseNode<T>::~ReviseNode()
{
	cout<<"calling dest\n";
}


template <class T>
const string& ReviseNode<T>::getVariable() const
{
	return variable;
}

/*
template <class T>
T ReviseNode<T>::getValue() const
{
	return value;
}*/

template <class T>
Constraint<T> * ReviseNode<T>::getConstraint() const
{
	return constraint;
}
