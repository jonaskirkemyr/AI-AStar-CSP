#ifndef MODULE2_H
#define MODULE2_H

#include "../view/Project.h"
#include "ofMain.h"
#include "ofColor.h"

#include <string>
#include "../settings/settings.h"
#include "../settings/functions.h"

#include "../models/file/cspGraph.h"
#include "../vertexC.h"
#include <vector>
using namespace std;


//template <typename T>
class Module2 : public Project
{
	private:
		//vector<string> equations;
		CSPGraph *cspG;
		VertexC * vertexC;

		string type;
		int k;

		void writeText(const string&,ofColor,int=(Settings::WIDTH/2)-50, int=(Settings::HEIGHT/2));

		const ofColor textColor;

		bool started;


	public:
		Module2(CSPGraph*&,int);
		~Module2();


		void setup();

		void update();
		void draw();
		void input(char);


		void notify();

		void setListenObj(Listener *);

		void setType(const string&);
		const string &getType() const;

		void printInfo();


		void square();




};

#endif