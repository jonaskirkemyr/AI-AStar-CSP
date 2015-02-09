#include "astarGAC.h"


/**
.#####...#####...######..##..##...####...######..######.
.##..##..##..##....##....##..##..##..##....##....##.....
.#####...#####.....##....##..##..######....##....####...
.##......##..##....##.....####...##..##....##....##.....
.##......##..##..######....##....##..##....##....######.
........................................................
**/
template <class T>
void AGac<T>::increaseC()//increase constraints obj
{
	Constraint<T> * temp=new Constraint<T>[size];

	for(int i=0;i<size;++i)
		temp[i]=constraints[i];

	delete constraints;

	maxSize*=2;//double the size
	constraints=new Constraint<T>[maxSize];

	for(int i=0;i<size;++i)
		constraints[i]=temp[i];

	delete temp;
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
AGac<T>::AGac(int maxSize)
{
	this->maxSize=maxSize;
	this->size=0;

	constraints=new Constraint<T>[this->maxSize];
	csp=new CSP<T>();
	astar=new AstarCSP();
}

template <class T>
void AGac<T>::addConstraint(Constraint<T> *c)
{
	if(size>=maxSize)
		increaseC();//increase size of constraints obj

	constraints[this->size]=*c;

	//cout<<constraints[this->size]

	++this->size;

	
}

template <class T>
void AGac<T>::init()
{
	for(int i=0;i<size;++i)
	{
		csp->addQueue(constraints[i]);
		csp->addConstraint(constraints[i]);
	}
	csp->printQueue();
	//for(int i=0;i<size;++i)
	//	constraints[i].printDomains();
	
	while(!csp->isQueueEmpty())
	{
		csp->domainFilter();
		csp->printQueue();
	}

	

	//for(int i=0;i<size;++i)
	//	constraints[i].printDomains();

	if(!isSolution())
	{
		//cout<<"Need to run astar!\n";
		SearchState *s=new SearchState(0);
		//cout<<"created search state\n";
		for(int i=0;i<size;++i)
		{
			string *temp=new string[constraints[i].getSize()];
			temp=constraints[i].getVariables();

			for(size_t j=0;j<constraints[i].getSize();++j)
			{
				//cout<<temp[j]<<endl;
				s->addDomain(constraints[i].getDomain(temp[j]));
			}
		}
		//cout<<"done creating search state\n";
		//s->printAll();//print domains in searchstate

		astar->addPtrCsp(csp);//add pointer to csp to astar algorithm
		astar->addPtrC(constraints,size);//add pointers to all constraints

		astar->init(s);//add start node
		astar->initStart();
		//cout<<"all initialized\n";

		int status=astar->runOnce();
		//cout<<"runned once\n";

		int numbRun=0;

		while(status!=1 && status!=-1)
		{
			//astar->printOpenList();

			if(numbRun>=1)
			{
				SearchState * current=dynamic_cast<SearchState*>(astar->getCurrent());


				int noColor=0;
				for(int i=0;i<current->getSize();++i)
					if(current->getSizeAt(i)!=1)
						++noColor;

				int i=0;
				Node* parent=astar->getCurrent()->getParent();
				while(parent)
				{
					//cout<<"check parent"<<endl;
					++i;
					parent=parent->getParent();

				}

				cout<<endl<<"-----RUN INFO AFTER "<<numbRun<<" RUNS-----"<<endl;
				//cout<<"#un const.:     "<<"0"<<endl;//won't finish if some constraints isn't fulfilled
				cout<<"#no color:      "<<noColor<<endl;
				cout<<"Path size:      "<<i<<endl;
				cout<<"#Nodes created: "<<astar->getNumbCreated()<<endl;
				cout<<"---END RUN INFO---"<<endl<<endl;
				cout<<">>";

				numbRun=0;
			}

			status=astar->runOnce();

			++numbRun;
		}
		//cout<<"DONE!"<<endl;

		SearchState * current=dynamic_cast<SearchState*>(astar->getCurrent());


		int noColor=0;
		for(int i=0;i<current->getSize();++i)
			if(current->getSizeAt(i)!=1)
				++noColor;

		int i=0;


		Node* parent=astar->getCurrent()->getParent();
		while(parent)
		{
			++i;
			parent=parent->getParent();

		}

		cout<<endl<<"-----RUN INFO-----"<<endl;
		cout<<"#un const.:     "<<"0"<<endl;//won't finish if some constraints isn't fulfilled
		cout<<"#no color:      "<<noColor<<endl;
		cout<<"Path size:      "<<i<<endl;
		cout<<"#Nodes created: "<<astar->getNumbCreated()<<endl;
		cout<<"---END RUN INFO---"<<endl<<endl;
		cout<<">>";


		//cout<<"GOAL FOUND!\n";
		current->printAll();
		//cout<<">>";
			
	}
	
	//cout<<"ORG:\n";
	//csp->printOriginalConstraints();
}

template <class T>
bool AGac<T>::isSolution()
{
	for(int i=0;i<size;++i)
		if((constraints[i].getNumberInDomain()/constraints[i].getSize())!=1)
			return false;
	return true;
}
