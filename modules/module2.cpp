#include "module2.h"


/**
.#####...#####...######..##..##...####...######..######.
.##..##..##..##....##....##..##..##..##....##....##.....
.#####...#####.....##....##..##..######....##....####...
.##......##..##....##.....####...##..##....##....##.....
.##......##..##..######....##....##..##....##....######.
........................................................
**/

void Module2::writeText(const string& write,ofColor c,int x,int y)
{
	ofSetColor(c);
	ofDrawBitmapString(write,x,y);
}




/**
.#####...##..##..#####...##......######...####..
.##..##..##..##..##..##..##........##....##..##.
.#####...##..##..#####...##........##....##.....
.##......##..##..##..##..##........##....##..##.
.##.......####...#####...######..######...####..
................................................
**/
Module2::Module2(CSPGraph *& g,int k):textColor(139,125,107)/*bisque 4*/ //equations,size
{
	this->cspG=new CSPGraph();
	this->k=k;

	this->cspG=g;

	vertexC=new VertexC(k,this->cspG->getNV(),this->cspG->getNE());
	type="cspastar";
	started=false;
}

Module2::~Module2()
{
	delete cspG;

	cspG=nullptr;
}


void Module2::setListenObj(Listener* app)
{
	//path->addListener(app);
}


void Module2::setup()
{
	

}

void Module2::update()
{
}

void Module2::draw()
{
	writeText("Press 's' to start",textColor,Settings::WIDTH/2-150);
	

	//writeText("K: "+getType(),textColor,0,Settings::HEIGHT-50);
}

void Module2::input(char key)
{
	if(key=='s')
	{
		if(started)
			return;
		started=true;
		for(int i=0;i<cspG->getNE();++i)
		{
			int * pos=cspG->getConnectionAt(i);
			if(pos)
				vertexC->setVariables(pos[0],pos[1]);
		}
		vertexC->registerConstraint();
		vertexC->run();
	}
	/*if(key=='1')
		Functions::square<double>(equations[0]);
	if(key=='2')
		Functions::square<double>(equations[1]);
	if(key=='3')
		Functions::square<double>(equations[2]);
	if(key=='4')
		Functions::square<double>(equations[3]);
	if(key=='5')
		Functions::square<double>(equations[4]);*/
}

void Module2::notify()
{

}

void Module2::setType(const string& type)
{
	vertexC->setK(Functions::strToInt(type));
}


const string &Module2::getType() const
{
	return "K: "+vertexC->getK();
	//return type;
	//return "tja";
}

void Module2::printInfo()
{
	/*Node *parent=path->getCurrent()->getParent();

	int i=0;
	while(parent)
	{
		++i;
		parent=parent->getParent();
	}*/

	/*cout<<endl<<"-----RUN INFO-----"<<endl;
		cout<<"Type:           "<<path->getType()<<endl;
		cout<<"Path size:      "<<i<<endl;
		cout<<"#Nodes created: "<<path->getNumbCreated()<<endl;
	cout<<"---END RUN INFO---"<<endl<<endl;
	cout<<">>";*/
}

