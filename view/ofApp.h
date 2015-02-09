#ifndef OFAPP_H
#define OFAPP_H

#include "ofMain.h"
#include "ofColor.h"


#include <iostream>
#include "Project.h"
#include "../models/listener.h"


class ofApp : public ofBaseApp, public Listener
{
	private:
		Project *project;
		int fps;

	public:
		ofApp();
		~ofApp();

		void setProject(Project *);
		Project * getProject() const;

		void setFPS(int);
		int getFPS();

		const string &getType() const;
		void setType(const string&);


		void setup();
		void update();
		void draw();

		void keyPressed(int);
		void keyReleased(int);
		void mouseMoved(int,int);
		void mouseDragged(int,int,int);
		void mousePressed(int,int,int);
		void mouseReleased(int,int,int);
		void windowResized(int,int);
		void dragEvent(ofDragInfo);
		void gotMessage(ofMessage);


		//listener:
		void handleNotification();
};

#endif
