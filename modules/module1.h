#ifndef MODULE1_H
#define MODULE1_H

#include "ofMain.h"
#include "ofColor.h"

#include "../view/Project.h"
#include "../pathFinding.h"
#include "../view/square.h"
#include "../models//map.h"

#include <iostream>
#include <string>




class Module1 : public Project
{
	private:
		int number;

		PathF *path;
		Square **squares;
		Map *maps;
		int mapSize;
		int mapIndex;

		string message;

		bool canDraw;
		bool gameOver;
		bool running;
		bool mapLoaded;
		bool goalFound;

		const ofColor start;//cyan
		const ofColor standard;//white
		const ofColor obstacle;//black
		const ofColor goal;//green
		const ofColor pathC;//red

		const ofColor textColor;
		const ofColor textColorLight;


		void initSquares();
		void setInitSquareColors(int**);

		void drawPath();
		void drawNode(Node*);

		void drawSquares();

		void writeText(const string&,ofColor,int=(Settings::WIDTH/2)-50, int=(Settings::HEIGHT/2));

		void loadMap(int);
		void initStart();


	public:
		Module1(Map*,int);
		~Module1();

		void setPath(PathF*);

		void setListenObj(Listener*);



		void setup();

		void update();
		void draw();
		void input(char);


		void notify();

		void setType(const string&);
		const string &getType() const;
		void printInfo();

};

#endif
