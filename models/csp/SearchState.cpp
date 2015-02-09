#include "searchState.h"

int SearchState::incrID=0;


void SearchState::increaseD()//increase constraints obj
{
	cout<<"start increase D\n";
	//Domain * temp=new Domain[size];
	
	
	/*Domain *temp=new Domain[size];
	for(int i=0;i<size;++i)
		temp[i]=domain[i];
	
	delete [] domain;

	maxSize*=2;
	domain=new Domain[maxSize];

	for(int i=0;i<size;++i)
		temp[i]=domain[i];
		*/



	/*for(int i=0;i<size;++i)
		temp[i]=domain[i];

	delete [] domain;

	maxSize*=2;//double the size
	domain=new Domain[maxSize];

	for(int i=0;i<size;++i)
		domain[i]=temp[i];*/

	//delete[] temp;
	cout<<"end increase D\n";
	//
}

 



SearchState::SearchState(int id,int ms) 
{
	setID(incrID++);
	maxSize=ms;
	size=0;
	//domain=new Domain[maxSize];

	posA=-1;
	posV=-1;

	srand (time(0));
    isGoal=false;
}

SearchState::SearchState(bool b)
{
	isGoal=true;
	size=0;

}

SearchState::SearchState(const SearchState &copy)
{
	setID(incrID++);
	size=copy.size;
	maxSize=copy.maxSize;

	posA=copy.posA;
	posV=copy.posV;
	isGoal=copy.isGoal;

	//domain=new Domain[size];

	for(int i=0;i<size;++i)
		domain[i]=copy.domain[i];
}



bool SearchState::addDomain(Domain * d)
{
	/*if(size>=maxSize)
		increaseD();//increase size of constraints obj

	for(int i=0;i<size;++i)
		if(domain[i].getParent()==d->getParent())
			return false;
	//cout<<"adding domain d: "<<d->getDomain()->size()<<endl;
	domain[size]=*d;
	++size;

	return true;*/

	for(int i=0;i<domain.size();++i)
		if(domain.at(i)->getParent()==d->getParent())
			return false;
	domain.push_back(new Domain(*d));
	return true;

}

int SearchState::getSize()
{
	return domain.size();
}

Domain * SearchState::getDomainAt(int i)
{
	if(i>domain.size() || i<0)
		i=0;
	return domain.at(i);
	//return &domain[i];
	
}

int SearchState::guess(int i)
{
	if(i>domain.size() || i<0)
		i=0;

	posA=i;

	/*int pos=rand()%domain[posA].getDomain()->size();

	posV=domain[posA].getDomain()->at(pos);

	domain[posA].getDomain()->clear();
	domain[posA].getDomain()->push_back(posV);*/

	int pos=rand()%domain.at(posA)->getDomain()->size();
	posV=domain.at(posA)->getDomain()->at(pos);
	domain.at(posA)->getDomain()->clear();
	domain[posA]->getDomain()->push_back(posV);

	return pos;
}

bool SearchState::guessValue(size_t pos,int i)
{
	if(i>domain.size() || i<0)
		i=0;

	posA=i;

	//cout<<"pos: "<<pos<<endl;

	/*posV=domain[posA].getDomain()->at(pos);
	//cout<<"posV: "<<posV<<endl;

	domain[posA].getDomain()->clear();
	domain[posA].getDomain()->push_back(posV);*/

	//cout<<"SIZE: "<<domain.at(posA)->getDomain()->size()<<endl;

	posV=domain.at(posA)->getDomain()->at(pos);
	domain.at(posA)->getDomain()->clear();
	domain.at(posA)->getDomain()->push_back(posV);

	return true;
}


int SearchState::getPosA()
{
	return posA;
}

double SearchState::getPosV()
{
	return posV;
}


size_t SearchState::getNumberInDomain()
{
	size_t numb=0;
	//for(int i=0;i<size;++i)
	for(int i=0;i<domain.size();++i)
	{
		numb+=(domain.at(i)->getDomain()->empty())?999:domain.at(i)->getDomain()->size();//set high heuristic if one domain is empty
			//domain.at(i)->getDomain()->size()==0)?
		//numb+=domain.at(i)->getDomain()->size();
	}
		//numb+=domain[i].getDomain()->size();

	return numb;
}


size_t SearchState::getSizeAt(int i)
{
	if(i<0 || i>=domain.size())return 99999;
	return domain.at(i)->getDomain()->size();
	//return domain[i].getDomain()->size();
}


void SearchState::printAll()
{
	//for(int i=0;i<size;++i)
	for(int i=0;i<domain.size();++i)
	{
		cout<<i<<": ";
		for(int j=0;j<domain.at(i)->getDomain()->size();++j)
			cout<<domain.at(i)->getDomain()->at(j)<<" ";
		//for(int j=0;j<domain[i].getDomain()->size();++j)
		//	cout<<domain[i].getDomain()->at(j)<<" ";
		cout<<endl;
	}
}

int SearchState::smallestDomain()
{
	size_t smallest=1;

	int pos=Settings::NOT_INIT;

	for(int i=0;i<domain.size();++i)
	{
		//cout<<domain[i].getDomain()->size()<<endl;
		//cout<<smallest<<endl;

		//cout<<(domain[i].getDomain()->size()>smallest)<<endl;


		if(domain.at(i)->getDomain()->size()>smallest)
		{
			smallest=domain.at(i)->getDomain()->size();
			pos=i;
		}

		/*if(domain[i].getDomain()->size()>smallest)
		{
			//cout<<"found smallest";
			smallest=domain[i].getDomain()->size();
			pos=i;
		}*/
	}
	return pos;
}




/**OPERATOR OVERLOADING**/
bool SearchState::operator==(const SearchState& right) const
{
	
	//cout<<"compare SEARCHSTATE\n";
	size_t numb=0;
	for(int i=0;i<domain.size();++i)
		numb+=domain.at(i)->getDomain()->size();
		//numb+=domain[i].getDomain()->size();

	size_t numb1=0;
	for(int i=0;i<right.domain.size();++i)
		numb1+=right.domain.at(i)->getDomain()->size();

	//check if some of vars is the goal
	if(isGoal && numb1/(right.domain.size()-1)==1)return true;
	else if(right.isGoal && numb/(domain.size()-1)==1) return true;
	
	
	return (posA==right.posA && posV==right.posV && posA!=-1 && posV!=-1 && right.posA!=-1 && right.posV!=-1);
	//return (numb==numb1 && numb/(size-1)==1);//check if singleton
}


bool SearchState::operator==(const Node& right) const
{
	
	

	//cout<<"compare SEARCHSTATE by virtual\n";
	const SearchState * first=dynamic_cast<const SearchState*>(this);
	const SearchState * second=dynamic_cast<const SearchState*>(&right);

	
	size_t numb=0;
	for(int i=0;i<first->domain.size();++i)
		numb+=first->domain.at(i)->getDomain()->size();


	size_t numb1=0;
	for(int i=0;i<second->domain.size();++i)
		numb1+=second->domain.at(i)->getDomain()->size();

	//check if some of vars is the goal
	if(first->isGoal && (double)numb1/(double)(second->domain.size())==1.0)return true;
	else if(second->isGoal && (double)numb/(double)(first->domain.size())==1.0) return true;
	
	
	return (first->posA==second->posA && first->posV==second->posV && first->posA!=-1 && first->posV!=-1 && second->posA!=-1 && second->posV!=-1);
	//return true;
	//return (numb==numb1 && numb/(size-1)==1);//check if singleton
}




SearchState& SearchState::operator=(const SearchState &right)
{
	if(this==&right)//if same object
		return *this;
	
	size=right.size;
	maxSize=right.maxSize;

	posA=right.posA;
	posV=right.posV;
	isGoal=right.isGoal;

	for(int i=0;i<right.domain.size();++i)
		domain.push_back(new Domain(*right.domain.at(i)));

	//domain=new Domain[size];

	/*for(int i=0;i<size;++i)
	{
		Domain *tempD=new Domain(right.domain[i]);
		domain[i]=*tempD;
	}*/
		//for(int j=0;j<right.domain[i].
		//domain[i]=right.domain[i];
	

	return *this;
}


void SearchState::setHeuristic(float h)
{
	Node::setHeuristic(h);
	//Node::setID(h);

}