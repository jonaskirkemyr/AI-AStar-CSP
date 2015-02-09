#ifndef SETTINGS_H
#define SETTINGS_H

#include <iostream>
#include <sstream>
using namespace std;


namespace Settings
{
	//screen size
	const int WIDTH=1024;
	const int HEIGHT=768;

	const string TITLE="IT3105 - Project 1";

	const string CREDIT="Created by: Jonas Kirkemyr";

	const int NOT_INIT=-999;

	const int TABLE_SIZE=96;
	const int MAX_TABLE_SIZE=64;//when to resize table


	//height and width of square objects
	const int S_WIDTH=100;
	const int S_HEIGHT=100;


	//cost of moving vertical/horizontal
	const int COST_MOVE=5;

	const int OBSTACLE=0;
	const int OPEN=1;
	const int START_POS=2;
	const int GOAL_POS=3;

	const int FPS=24;



};







#endif // SETTINGS_H
