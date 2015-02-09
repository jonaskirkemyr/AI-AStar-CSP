#include "module1.h"
#include "../settings/functions.h"

/**
.#####...#####...######..##..##...####...######..######.
.##..##..##..##....##....##..##..##..##....##....##.....
.#####...#####.....##....##..##..######....##....####...
.##......##..##....##.....####...##..##....##....##.....
.##......##..##..######....##....##..##....##....######.
........................................................
**/
void Module1::initSquares()
{
	squares=new Square*[path->getHeight()];
	for(int i=0;i<path->getHeight();++i)
		squares[i]=new Square[path->getWidth()];

	for(int i=0;i<path->getHeight();++i)
	{
		for(int j=0;j<path->getWidth();++j)
		{

			squares[i][j].setXPos((float)j*Settings::WIDTH/(float)path->getHeight());
			squares[i][j].setYPos((float)i*Settings::HEIGHT/(float)path->getWidth());
			squares[i][j].setWidth((float)Settings::WIDTH/(float)path->getWidth());
			squares[i][j].setHeight((float)Settings::HEIGHT/(float)path->getHeight());

		}
	}
}

void Module1::setInitSquareColors(int ** map)
{

	for(int i=0;i<path->getHeight();++i)
	{
		for(int j=0;j<path->getWidth();++j)
		{

			/**INITIALIZE COLORS!!!**/
			if(map[i][j]==Settings::OBSTACLE)//obstacle
				squares[i][j].setColor(obstacle);
			if(map[i][j]==Settings::OPEN)//open
				squares[i][j].setColor(standard);
			if(map[i][j]==Settings::START_POS)//start
				squares[i][j].setColor(start);
			if(map[i][j]==Settings::GOAL_POS)//goal
				squares[i][j].setColor(goal);

		}
	}
}

void Module1::drawPath()
{
	Node * temp=path->getCurrent();

	Node *parent=temp->getParent();
	drawNode(temp);
	int i=0;
	while(parent)
	{
		++i;
		drawNode(parent);
		parent=parent->getParent();
	}
	//cout<<"length:"<<i<<endl;
}



void Module1::drawNode(Node * node)
{
	int column=path->getColumnFromPos(node->getID());
	int row=path->getRowFromPos(node->getID());

	squares[column][row].drawWithColor(pathC);

}

void Module1::drawSquares()
{
	for(int i=0;i<path->getHeight();++i)
		for(int j=0;j<path->getWidth();++j)
			squares[i][j].draw();
}

void Module1::writeText(const string& write,ofColor c,int x,int y)
{
	ofSetColor(c);
	ofDrawBitmapString(write,x,y);
}

void Module1::loadMap(int i)
{
	if(i>=0 && i<mapSize && !running)//load map only if legal position is entered
	{
		goalFound=false;
		//ofSetBackgroundAuto(true);
		mapIndex=i;
		path->setWidth(maps[i].getWidth());
		path->setHeight(maps[i].getHeight());
		path->setMap(maps[i].getMap());

		message="Map loaded: "+Functions::intToStr(i);
		mapLoaded=true;

		//ofSetBackgroundAuto(true);

	}
}

void Module1::initStart()
{

	if(running || !mapLoaded)return;

	if(gameOver)//load same map again if first run is done
		loadMap(mapIndex);

	gameOver=false;
	canDraw=false;

	path->initStart();

	initSquares();//create empty squares
	setInitSquareColors(path->getMap());

	running=true;
	//ofSetBackgroundAuto(true);

}


/**
.#####...##..##..#####...##......######...####..
.##..##..##..##..##..##..##........##....##..##.
.#####...##..##..#####...##........##....##.....
.##......##..##..##..##..##........##....##..##.
.##.......####...#####...######..######...####..
................................................
**/

Module1::Module1(Map * maps,int size) : start(0,255,255)/*cyan*/,standard(255,255,255)/*white*/,
				 obstacle(0,0,0)/*black*/,goal(0,255,0)/*green*/,pathC(255,0,0)/*red*/,
				 textColor(139,125,107)/*bisque 4*/, textColorLight(205,183,158)/*bisque 3*/
{

	mapIndex=Settings::NOT_INIT;
	mapSize=size;
	this->maps=new Map[mapSize];

	for(int i=0;i<mapSize;++i)
		this->maps[i]=maps[i];

	path=new PathF();
	//path->addListener(this);

	squares=nullptr;

	canDraw=false;
	gameOver=false;
	running=false;
	mapLoaded=false;
	goalFound=false;
	message="Map not loaded";
}

Module1::~Module1()
{

	for(int i=0;i<path->getHeight();++i)
		delete[] squares[i];
	delete[] squares;

	squares=nullptr;

	delete path;
	delete maps;

	path=nullptr;
	maps=nullptr;

	//ofExit();

}


void Module1::setListenObj(Listener* app)
{
	path->addListener(app);
}



void Module1::setup()
{

}


void Module1::update()
{
	if(gameOver || !running)return;

	int status=path->runOnce();
	if(status==1 || status==-1)//goal found or error -> open list empty -> no more nodes to search for
	{
		gameOver=true;
		running=false;
		goalFound=true;
	}
}

void Module1::draw()
{
	if(!mapLoaded)
		writeText("Load map by pressing a number between [1-9], then press 's' to start",textColor,Settings::WIDTH/2-150);
	
	if(goalFound)
	{
		drawSquares();
		drawPath();
	}


	//only draw when a new node is pushed into open
	if(canDraw)
	{
		drawSquares();
		drawPath();
		canDraw=false;

		if(gameOver)
		{
				drawSquares();
				drawPath();
				writeText("Run complete. Please exit the window",textColor);
				
				printInfo();

				drawPath();
				//ofSetBackgroundAuto(false);
				//ofSetBackgroundAuto(true);
				
				//path->setCurrent(path->getGoal());
				//ofSetBackgroundAuto(false);
				return;
		}
	}
	writeText("Type:"+path->getType(),textColorLight,0,Settings::HEIGHT-50);
	writeText(message,textColorLight,0,Settings::HEIGHT-20);
}

void Module1::input(char key)
{
	if(key=='s')
		initStart();
	else if(key>= 49 && key<=57)//key between [1-9]
		loadMap(key-49);
}

void Module1::notify()
{
	canDraw=true;
}

void Module1::setType(const string& type)
{
	if(type=="astar" || type=="bfs" || type=="dfs")
		path->setType(type);
}

const string &Module1::getType() const
{
	return path->getType();
}

void Module1::printInfo()
{

	Node *parent=path->getCurrent()->getParent();

	int i=0;
	while(parent)
	{
		++i;
		parent=parent->getParent();
	}

	cout<<endl<<"-----RUN INFO-----"<<endl;
		cout<<"Type:           "<<path->getType()<<endl;
		cout<<"Path size:      "<<i<<endl;
		cout<<"#Nodes created: "<<path->getNumbCreated()<<endl;
	cout<<"---END RUN INFO---"<<endl<<endl;
	cout<<">>";
}
