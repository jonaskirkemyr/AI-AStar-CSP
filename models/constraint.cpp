#include "constraint.h"

/**
.#####...#####...######..##..##...####...######..######.
.##..##..##..##....##....##..##..##..##....##....##.....
.#####...#####.....##....##..##..######....##....####...
.##......##..##....##.....####...##..##....##....##.....
.##......##..##..######....##....##..##....##....######.
........................................................
**/

/**
 * loop through all domains in current constraint to check
 * if set value for a value can be used
 */
template <class T>
bool Constraint<T>::loopDomain(vector<string>& v,
                            int pos,
                            exprtk::expression<T>& expression,
                            map<string,T>* vars)
{

	if(pos>=v.size())return false;

	for(int i=0;i<this->variables[v.at(pos)]->size();++i)
	{
		cout<<v.at(pos)<<variables[v.at(pos)]->at(i)<<endl;
		vars->at(v.at(pos))=variables[v.at(pos)]->at(i);


		if(pos>=(v.size()-1))//if last vector to check
		{
			if(expression.value())//run expression
				return true;
		}
		else if(loopDomain(v,pos+1,expression,vars))//go to a deeper level
				return true;

	}

	return false;
}


/**
.#####...##..##..#####...##......######...####..
.##..##..##..##..##..##..##........##....##..##.
.#####...##..##..#####...##........##....##.....
.##......##..##..##..##..##........##....##..##.
.##.......####...#####...######..######...####..
................................................
**/

/** CONSTRUCTORS**/
template <class T>
Constraint<T>::Constraint()
{
	//constraint="";
}

template <class T>
Constraint<T>::Constraint(const string& c)
{
	setConstraint(c);
}
template <class T>
Constraint<T>::Constraint(const Constraint& copy)
{
	cout<<"copy"<<endl;
	strC=copy.strC;
	//variables=copy.variables;

	for(auto i=copy.variables.begin();i!=copy.variables.end();++i)
	{
		vector<T> *tempDomain=new vector<T>();
		for(int j=0;j<i->second->size();++j)
			tempDomain->push_back(i->second->at(j));


		variables.emplace(i->first,tempDomain);
	}

	cout<<"end copy?\n";
}

template <class T>
Constraint<T>::~Constraint()
{
	cout<<"destructor constraint\n";
}
/** END CONSTRUCTORS**/








template <class T>
void Constraint<T>::setConstraint(const string& c)
{
	strC=c;
}

template <class T>
const string & Constraint<T>::getConstraint() const
{
	return strC;
}



template <class T>
void Constraint<T>::addVariable(const string & variableName,vector<T>* domain)
{

	//variables[variableName]=domain;
	variables.emplace(variableName,domain);
	//emplace
}


template <class T>
vector<T> * Constraint<T>::getDomain(const string& variable) const
{
	typename unordered_map<string,vector<T>*>::const_iterator check = variables.find(variable);
	if(check!=variables.end())
		return check->second;//returns the reference to the domain vector
	return nullptr;
}



//check if value exists in domain of variable
template <class T>
bool Constraint<T>::isInDomain(const string& variable,T value,bool del)
{
	vector<T> *domain=variables[variable];

	for(int i=0;i<domain->size();++i)
		if(domain->at(i)==value)
		{
			if(del)
				domain->erase(domain->begin()+i);
			return true;
		}
	return false;
}

template <class T>
bool Constraint<T>::posInDomain(const string& variable,int pos)
{
	vector<T> *domain=variables[variable];
	return domain->size()>=pos;
}

/*
void Constraint::getSizeDomains(int*& array,int& size)
{
	//create array, check number of elements in each domain
	size=variables.size();

	array=new int[size];

	int pos=0;
	for(auto i=variables.cbegin();i!=variables.cend();++i)
	{
		array[pos]=i->second.size();
		++pos;
	}
}*/

template <class T>
void Constraint<T>::fillQueue(list<ReviseNode<T>*>& tempQ,int numb)
{
	//fills up queue with all variables in constraint, and their domain values
	for(auto i=variables.begin();i!=variables.end();++i)
		for(int j=0;j<i->second->size();++j)
			tempQ.push_back(new ReviseNode<T>(i->first,i->second->at(j),numb));
}


template <class T>
void Constraint<T>::fillQueue(list<ReviseNode<T>*>* tempQ)
{
	cout<<"start fill queue\n";
	Constraint<T>*ptr=this;
	for(auto i=variables.begin();i!=variables.end();++i)
	{
		//for(int j=0;j<i->second->size();++j)
		cout<<i->first<<endl;
		tempQ->push_back(new ReviseNode<T>(i->first));
		//tempQ->push_back(new ReviseNode<T>(i->first,ptr));
	}
	cout<<"end fill queue";
}



template <class T>
bool Constraint<T>::checkSatisfaction(const string & var,T value)
{

	vector<string> var_domains;//saves the variable name in a vector
	map<string,T> vars;

	exprtk::symbol_table<T> symbol_table;

	symbol_table.add_variable(var,value);
	
	for(auto i=variables.begin();i!=variables.end();++i)
	{
		if(i->first==var)continue;//go to next variable in constraint, because this value is already set

		//vars.insert({i->first,i->second->at(0)});
		vars[i->first]=i->second->at(0);

		symbol_table.add_variable(i->first,
			vars[i->first]);
		var_domains.push_back(i->first);
	}
	//return true;
	symbol_table.add_constants();

	exprtk::expression<T> expression;
	expression.register_symbol_table(symbol_table);

	exprtk::parser<T> parser;
	parser.compile(strC,expression);

	//int numberOfVars=var_domains.size();

	//return loopDomain(var_domains,0,expression,&vars);

	return loopDomain(var_domains,0,expression,&vars);

}

template <class T>
bool Constraint<T>::removeFromDomain(const string& var,T value)
{
	return isInDomain(var,value,true);

}


template <class T>
void Constraint<T>::printDomains()
{
	for(auto i=variables.begin();i!=variables.end();++i)
	{
		cout<<i->first<<" ";
		for(int j=0;j<i->second->size();++j)
			cout<<i->second->at(j)<<" ";
		cout<<endl;
	}

}

template <class T>
const unordered_map<string,vector<T>*> &Constraint<T>::getAllVariables() const
{
	return variables;
}

template <class T>
string * Constraint<T>::getVariables()
{
	string *vars=new string[getSize()];
	int pos=0;
	for(auto i=variables.begin();i!=variables.end();++i)
	{
		vars[pos]=i->first;
		++pos;
	}

	return vars;

}

template <class T>
size_t Constraint<T>::getSize()
{
	return variables.size();
}