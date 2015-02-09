#ifndef PROJECT_H
#define PROJECT_H

#include <iostream>
#include <string>


#include "../models/listener.h"
#include "../settings/settings.h"

//#include "settings/functions.h"

//#include "view/ofApp.h"

//#include "view/ofApp.h"


using namespace std;




class Project
{
	//protected:
		//Project();
	public:
		//abstract
		virtual void setup()=0;

		virtual void update()=0;
		virtual void draw()=0;
		virtual void input(char)=0;

		virtual void notify()=0;

		virtual void setListenObj(Listener *)=0;

		virtual void setType(const string&)=0;
		virtual const string &getType() const=0;

		virtual void printInfo()=0;

};


#endif
