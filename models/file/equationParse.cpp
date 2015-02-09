#include "equationParse.h"

EquationParse::EquationParse()
{
	//equations=new string[getMaxSize()];
	cspG=new CSPGraph();

}

void EquationParse::reset()
{
	delete cspG;
	cspG=new CSPGraph();
}

void EquationParse::readDelimiter(vector<string>& split)
{
	int lineNumb=getSize();

	//for(size_t i=0;i<split.size();++i)//add info to map
   // {
		//cout<<split.at(i)<<endl;
		if(lineNumb==0)
		{
			cspG->setNV(Functions::strToInt(split.at(0)));
			cspG->setNE(Functions::strToInt(split.at(1)));
			cspG->initArrays();
		}
		else if(lineNumb>0 && lineNumb<=cspG->getNV())
		{
			cspG->addCoordinate(stof(split.at(1)),stof(split.at(2)));
		}
		else
		{
			cspG->addConnections(Functions::strToInt(split.at(0)),Functions::strToInt(split.at(1)));
		}
		//cout<<endl;
  //  }

}

void EquationParse::increase()
{
}

void EquationParse::get(int i,CSPGraph*& s)
{
    s=cspG;
}

void EquationParse::get(CSPGraph*& s)
{
    s=cspG;
}
