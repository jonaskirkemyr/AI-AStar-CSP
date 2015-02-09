#include "csp.h"


/**
.#####...#####...######..##..##...####...######..######.
.##..##..##..##....##....##..##..##..##....##....##.....
.#####...#####.....##....##..##..######....##....####...
.##......##..##....##.....####...##..##....##....##.....
.##......##..##..######....##....##..##....##....######.
........................................................
**/






template <class T>
bool CSP<T>::revise(ReviseNode<T>* node)
{
	
	vector<T> *tempDomain=node->getConstraint()->getDomain(node->getVariable());

	vector<T> tempRemove;


	bool reduced=false;
	for(size_t i=0;i<tempDomain->size();++i)
	{
		if(!node->getConstraint()->checkSatisfaction(node->getVariable(),tempDomain->at(i)))
		{
			reduced=true;
			tempRemove.push_back(tempDomain->at(i));
		}
	}

	for(size_t i=0;i<tempRemove.size();++i)
	{
		cout<<"REMOVE: "<<node->getVariable()<<" "<<tempRemove.at(i)<<endl;
		node->getConstraint()->removeFromDomain(node->getVariable(),tempRemove.at(i));
	}

	return reduced;
}






template <class T>
bool CSP<T>::valueExistsInDomain(const string& variable,T value,int c)
{
	if(size>=c)
		return constraints[c].isInDomain(variable,value);
	return false;
}

template <class T>
bool CSP<T>::posExistsInDomain(const string& variable,int pos,int c)
{
	if(size>=c)
		return constraints[c].posInDomain(variable,pos);
	return false;
}




template <class T>
void CSP<T>::printQueue()
{
	for(typename list<ReviseNode<T>*>::iterator i=queue.begin();i!=queue.end();++i)
		cout<<(*i)->getVariable()<<" ";
	cout<<endl;
}





/**
.#####...##..##..#####...##......######...####..
.##..##..##..##..##..##..##........##....##..##.
.#####...##..##..#####...##........##....##.....
.##......##..##..##..##..##........##....##..##.
.##.......####...#####...######..######...####..
................................................
**/
template <class T>
CSP<T>::CSP()
{

}


template <class T>
bool CSP<T>::domainFilter()
{
	if(!isQueueEmpty())
	{
		printQueue();
		//retrieve first reviseNode in queue and pop it
		ReviseNode<T> *temp=queue.front();

		queue.pop_front();

		bool test=revise(temp);
		//cout<<"REVISE:"<<test<<endl;

		if(test)//value satisfy constraint for at least 1pair of values in other domains
			rerun(temp);

		

		//cout<<"Node:"<<temp->getValue()<<" "<<temp->getVariable()<<endl;
		//cout<<"REVISE:"<<test<<endl;
	}

	return false;
}

template <class T>
bool CSP<T>::isQueueEmpty()
{
	return queue.empty();
}




template <class T>
bool CSP<T>::rerun(ReviseNode<T>* node)
{
	/*for(int i=0;i<size;++i)//loop through all constraints, look for variable in constraint, and add all values in domain EXCEPT the one set in ReviseNode*node
	{
		vector<T>* tempDomain=constraints[i].getDomain(node->getVariable());
		if(tempDomain)//variable exists in constraint (doesn't return nullptr)
		{
			for(size_t j=0;j<tempDomain->size();++j)
			{
				if(tempDomain->at(j)==node->getValue())continue;//go to next value in domain if same
				cout<<"adding "<<node->getVariable()<<" "<<tempDomain->at(j)<<endl;
				this->queue.push_back(new ReviseNode<T>(node->getVariable(),tempDomain->at(j),i));
			}
		}
	}*/

	return true;
}

template <class T>
list<ReviseNode<T>*> *CSP<T>::getQueue()
{
	return &queue;
}


template <class T>
void CSP<T>::addQueue(Constraint<T>& c)
{
	string *temp=new string[c.getSize()];
	temp=c.getVariables();

	for(size_t i=0;i<c.getSize();++i)
		queue.push_back(new ReviseNode<T>(temp[i],&c));

	
}


template <class T>
void CSP<T>::addConstraint(Constraint<T> &c)
{
	

	//constraints[this->size]=Constraint<T>(c);
	//constraints[this->size]=c;
	constraints.push_back(new Constraint<T>(c));
	//constraints[this->size]=*c;
	cout<<"end copy\n";
	//constraints[this->size]=*c;

	
}

template <class T>
void CSP<T>::printOriginalConstraints()
{
	for(size_t i=0;i<constraints.size();++i)
		constraints.at(i)->printDomains();
}