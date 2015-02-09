#include "../view/ofApp.h"

/**
.#####...#####...######..##..##...####...######..######.
.##..##..##..##....##....##..##..##..##....##....##.....
.#####...#####.....##....##..##..######....##....####...
.##......##..##....##.....####...##..##....##....##.....
.##......##..##..######....##....##..##....##....######.
........................................................
**/



/**
.#####...##..##..#####...##......######...####..
.##..##..##..##..##..##..##........##....##..##.
.#####...##..##..#####...##........##....##.....
.##......##..##..##..##..##........##....##..##.
.##.......####...#####...######..######...####..
................................................
**/

ofApp::ofApp()
{
	fps=Settings::FPS;
	project=nullptr;

}

ofApp::~ofApp()
{
	delete project;
	ofExit();//exit the app
}

void ofApp::setProject(Project *p)
{
	if(project!=nullptr)
		delete project;
	project=p;
	project->setListenObj(this);

}

Project *ofApp::getProject() const
{
	return project;
}

void ofApp::setFPS(int f)
{
	fps=f;
	ofSetFrameRate(fps);
}

int ofApp::getFPS()
{
	return fps;
}

const string &ofApp::getType() const
{
	return project->getType();
}

void ofApp::setType(const string& type)
{
	project->setType(type);
}








//OPEN FRAMEWORK
void ofApp::setup()
{
	ofSetFrameRate(fps);
	if(project)//check if not nullptr
		project->setup();
}

void ofApp::update()
{
	//cout<<"update "<<project<<endl;
	if(project)//check if not nullptr
		project->update();
}

void ofApp::draw()
{
	if(project)//check if not nullptr
		project->draw();
}



void ofApp::keyPressed(int key)
{
	if(project)//check if not nullptr
		project->input(key);
}


//NOT USED - NOT IMPL
void ofApp::keyReleased(int key){}
void ofApp::mouseMoved(int x, int y ){}
void ofApp::mouseDragged(int x, int y, int button){}
void ofApp::mousePressed(int x, int y, int button){}
void ofApp::mouseReleased(int x, int y, int button){}
void ofApp::windowResized(int w, int h){}
void ofApp::dragEvent(ofDragInfo dragInfo){}
void ofApp::gotMessage(ofMessage msg){}
//END OPEN FRAMEWORK



void ofApp::handleNotification()
{
	if(project)//check if not nullptr
		project->notify();
}
