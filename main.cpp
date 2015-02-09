//#include "ofMain.h"

#include "view/ofApp.h"

#include "view/Project.h"

#include <string>

#include "settings/settings.h"


#include "pathFinding.h" 
#include "models/node.h"

#include "models/file/StringSplit.h"
#include "models/file/fileParse.h"
#include "models/file/mapParse.h"
#include "models/file/equationParse.h"

#include "models/map.h"

#include "settings/coolText.h"

#include <iostream>

#include "view/threadWindow.h"
#include "modules/module1.h"
#include "modules/module2.h"


#include "settings/functions.h"

//#include "cspTest.h"


//#include "models/constraint.h"
/*#include "models/csp/constraint.h"

#include "models/csp/astarGAC.h"


#include "models/csp/Expression.h"
#include "models/csp/domain.h"
#include "models/csp/astarCSP.h"*/

#include "vertexC.h"

//#include "models/file/cspGraph.h"

using namespace std;
 

/**
			 _____ _____ _____  __  _____ _____           ___  ___          _       _   __
			|_   _|_   _|____ |/  ||  _  |  ___|          |  \/  |         | |     | | /  |
			  | |   | |     / /`| || |/' |___ \   ______  | .  . | ___   __| |_   _| | `| |
			  | |   | |     \ \ | ||  /| |   \ \ |______| | |\/| |/ _ \ / _` | | | | |  | |
			 _| |_  | | .___/ /_| |\ |_/ /\__/ /          | |  | | (_) | (_| | |_| | | _| |_
			 \___/  \_/ \____/ \___/\___/\____/           \_|  |_/\___/ \__,_|\__,_|_| \___/

				          ,       ,				          	  ,       ,
				        ./(       )\.				        ./(       )\.
				        )  \/\_/\/  (				        )  \/\_/\/  (
				        `)  (^Y^)  (`				        `)  (^Y^)  (`
				         `),-(~)-,(`  				  	     `),-(~)-,(`
				             '"'				                 '"'

				   ___                         _   ___      _
				  |_  |                       | | / (_)    | |
				    | | ___  _ __   __ _ ___  | |/ / _ _ __| | _____ _ __ ___  _   _ _ __
				    | |/ _ \| '_ \ / _` / __| |    \| | '__| |/ / _ \ '_ ` _ \| | | | '__|
				/\__/ / (_) | | | | (_| \__ \ | |\  \ | |  |   <  __/ | | | | | |_| | |
				\____/ \___/|_| |_|\__,_|___/ \_| \_/_|_|  |_|\_\___|_| |_| |_|\__, |_|
				                                                                __/ |
				                                                               |___/
				          ,       ,				          	  ,       ,
				        ./(       )\.				        ./(       )\.
				        )  \/\_/\/  (				        )  \/\_/\/  (
				        `)  (^Y^)  (`				        `)  (^Y^)  (`
				         `),-(~)-,(`  				  	     `),-(~)-,(`
				             '"'				                 '"'
**/

//static Module1 module1;
//

static bool newFile=false;
static int k=4;


void menu(vector<string>& v,FileParse *& file,Project *project,ofApp *app,ThreadWin & tWin,string &type)
{
	for(int i=0;i<v.size();++i)
	{
		string input=v.at(i);

		if(input=="open" && file)//opening file
		{
			if((i+1)<v.size())
			{
				if(file)
					file->openFile(v.at(i+1));
				++i;
			}
			else
				cout<<"You need to specify a filename."<<endl;
		}//end open
		else if(input=="read" && file)//reading file
		{

			if(file->readFile())
			{
				cout<<file->getSize()<<" entries loaded"<<endl;
				newFile=true;
			}
			else
				cout<<"Make sure to open a file before trying to read.\n";
		}//end read
		else if(input=="print" && file)
		{

			if(!file)
			{
				cout<<"Make sure to set the type and open a file before running this command.\n";
				return;
			}

			int posPrint=0;

			if(v.size()>(i+1))
			{
				try
				{
					//posPrint=atoi(v.at(i+1).c_str());
					posPrint=Functions::strToInt(v.at(i+1));
					++i;
				}
				catch(std::invalid_argument&)
				{

				}
			}

			if(type=="module1")
			{
				Map * map;
				if(file)
					file->get(posPrint,map);
				if(map)//nullptr wasn't returned
				{
					//cout<<map<<endl;
					//cout<<"not nullptr\n";
					map->printMap();
				}
				else
					cout<<"Map not loaded. Try loading the map, or another index"<<endl;
			}
			else if(type=="module2")
			{
				/*string *equation;
				file->get(posPrint,equation);

				if(equation)
					cout<<endl<<equation<<endl;
				else
					cout<<"Equation not loaded. Try loading the equation, or another index"<<endl;*/
				cout<<"Can't print this amount of data :)"<<endl;
			}


		}//end print
		else if(input=="run" &&file)
		{


			if(type=="module1")
			{

				if(!app->getProject() || newFile)
				{
					Map* maps;
					file->get(maps);
					app->setProject(new Module1(maps,file->getSize()));
					newFile=false;
				}

				if(v.size()>(i+1))
				{
					app->setType(v.at(i+1));
					++i;
				}

			}
			else if(type=="module2")
			{
				if(!app->getProject() || newFile)
				{
					CSPGraph * graph;

					file->get(graph);
					app->setProject(new Module2(graph,k));//number of colors!
					newFile=false;
				}
				if(v.size()>(i+1))
				{
					/*app->setType(v.at(i+1));
					++i;*/
					cout<<"This module doesn't have a type"<<endl;
				}
			}
			else
				return;//no accepted type selected


			if(!tWin.isRunning())
				tWin.start();



		}//end run
		else if(input=="help")
		{
			cmnds();

			cout<<"ACTION\t \tCOMMAND         \t \tDESCRIPTION"<<endl<<endl;
			cout<<"OPEN  \t-\t open <filename>\t-\tOpens a file by name."<<endl;
			cout<<"READ  \t-\t read           \t-\tRead an already opened file."<<endl;
			cout<<"RUN   \t-\t run <type>     \t-\tRun algorithms. (bfs,dfs,astar)"<<endl<<endl;

			cout<<"PRINT \t-\t print <index=0>\t-\tPrints a loaded map by index."<<endl;
			cout<<"FPS   \t-\t fps <int>      \t-\tSet/Show FPS."<<endl;
			cout<<"EXIT  \t-\t exit           \t-\tExit the program."<<endl;
			cout<<"ABOUT \t-\t about          \t-\tShow about info"<<endl;
		}//end help
		else if(input=="exit")
		{
			cout<<"Bye!"<<endl;
			if(tWin.isRunning())
				tWin.stop();
			ofExit();
		}//end exit
		else if(input=="about")
		{
			aboutTxt();
		}//end about
		else if(input=="type")
		{
			if((i+1)<v.size())
			{
				type=v.at(i+1);
				++i;

				//if(file)//free memory before initializing new module
				//	delete file;
				if(type=="module1")
					file=new MapParse();
				else if(type=="module2")
					file=new EquationParse();
			}
			else
				cout<<"You need to specify a type."<<endl;
		}
		else if(input=="fps")
		{
			if((i+1)<v.size())
			{
				int fps=Functions::strToInt(v.at(i+1));
				app->setFPS(fps);
				++i;
			}
			else
				cout<<"Current FPS: "<<app->getFPS()<<endl;
		}
		else if(input=="k")
		{
			if((i+1)<v.size())
			{
				k=Functions::strToInt(v.at(i+1));
				++i;
			}
			else
				cout<<"Current K: "<<k<<endl;
		}

		else
		{
			if(!file)
				cout<<"Make sure to set the type before running this command.\n";
			else
				cout<<"Unknown command '"<<input<<"'. Type 'help' to see available commands"<<endl;
		}


	}
}









int main()
{





	
	/*VertexC *vertex=new VertexC(4,6);

	vertex->setVariables(0,0,1);
	vertex->setVariables(1,0,2);
	vertex->setVariables(2,0,3);
	vertex->setVariables(3,1,2);
	vertex->setVariables(4,1,3);
	vertex->setVariables(5,2,3);

	vertex->registerConstraint();
	vertex->run();




	//for(size_t i=0;i<x_values.size();++i)
	//	cout<<x_values.at(i)<<" ";


     
   // cTest.addConstraint(c);
	//cTest.addConstraint(d);
    
	//cTest.initTest();
	//cTest.start();


	//csp.addConstraint(c);



	return 0;*/



	FileParse * file=nullptr;

	string input;
	string fileName;

	vector<string>cmds;
	string delimiter=" ";

	Project *project=nullptr;
	ofApp *app=new ofApp();

	ThreadWin tWin(app);
	string type;
	//tWin.start();

	startMsg();//prints welcome msg



	while(input!="exit")
	{
		cout<<"\n>>";
		getline(cin,input);

		if(input.empty())continue;//don't want to process an empty command

		Split::splitString(input,cmds,delimiter);
		menu(cmds,file,project,app,tWin,type);



		cmds.clear();
	}

	return 0;

/*

	FileParse file;
	if(file.openFile("test.txt"))
	{
		file.readFile();



		Map * map=file.getMap();
		int** board=map->getMap();





		PathF *path=new PathF(board,map->getWidth(),map->getHeight());

		ofApp *app=new ofApp();
		path->addListener(app);
		app->setPath(path);



		ofSetupOpenGL(Settings::WIDTH,Settings::HEIGHT,OF_WINDOW);

		ofSetWindowTitle(Settings::TITLE);
		ofRunApp(app);

	}*/




				// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:




    cout<<"APP EXIT WITH CODE (0)";
	return 0;

}


