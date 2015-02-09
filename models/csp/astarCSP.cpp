#include "astarCSP.h"

AstarCSP::AstarCSP()
{
	srand (time(0));
}


void AstarCSP::init(SearchState *ss)
{
	//ss->setID(0);
	nodes.emplace(ss->getID(),ss);
	setStart(dynamic_cast<SearchState*>(ss));
	setGoal(dynamic_cast<SearchState*>(new SearchState(true)));
} 

float AstarCSP::arcCost(Node*a,Node*b)
{
	return 0.0;
}

void AstarCSP::computeHeuristic(Node* n)
{
	
	if(SearchState *temp=dynamic_cast<SearchState*>(n))
	{
		if(n!=getStart())
		{
			int dSize=temp->getSize();

			for(int i=0;i<dSize;++i)
			{
				for(int j=0;j<constraints.size();++j) 
				{
			
					string variable=constraints.at(j)->setDomain(temp->getDomainAt(i));
					if(!variable.empty())
					{
						csp->rerun(new ReviseNode<double>(variable,*constraints.at(j)));//rerun var with constraints
					}
				}
			}
			cout<<"QUEUE IS NOW:\n";
			csp->printQueue();
			cin>>dSize;
			//cout<<"FILTERING!"<<endl;

			while(!csp->isQueueEmpty())
				csp->domainFilter();
		}
		n->setHeuristic(temp->getNumberInDomain()-temp->getSize());
	}
}

void AstarCSP::generateNeighbours(int i,vector<Node* >& nodes)
{
		 
	if(SearchState *temp=dynamic_cast<SearchState*>(this->nodes[i]))
	{
		int pos=temp->smallestDomain();

		size_t startPV=(temp->getDomainAt(pos)->getDomain()->size()>2)?2:temp->getDomainAt(pos)->getDomain()->size();//max children to generate

		for(size_t j=startPV;j>=1;j--)//after picking domaing with smallest size, a given amount is chosen to look at further
		{
			SearchState *child=new SearchState(0);
			*child=*temp;

			child->guessValue(j-1,pos);

			nodes.push_back(dynamic_cast<SearchState*>(child));
		}



	}
}

void AstarCSP::addPtrC(Constraint<double>* c,int cSize)
{ 
	for(int i=0;i<cSize;++i)
		constraints.push_back(&c[i]);
}

void AstarCSP::addPtrCsp(CSP<double>* c)
{
	csp=c;
}