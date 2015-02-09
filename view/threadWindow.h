#ifndef THREAD_WIN_H
#define THREAD_WIN_H

#include "ofMain.h"

#include "../view/ofApp.h"

#include "ofThread.h"
#include "../settings//settings.h"

class ThreadWin : public ofThread
{
	private:
		ofApp* app;
		bool running;


	public:
		ThreadWin(ofApp*);

		 void start()
	    {
	        // Mutex blocking is set to true by default
	        // It is rare that one would want to use startThread(false).
	        //cout<<"start\n";
	        running=true;
	        startThread();
	        
	    }

	    bool isRunning(){return running;}

	    void stop()
	    {
	    	//cout<<"stop\n";
	    	running=false;
	        stopThread();
	    }

	    void threadedFunction()
	    {
	    	ofSetupOpenGL(Settings::WIDTH,Settings::HEIGHT,OF_WINDOW);

			ofSetWindowTitle(Settings::TITLE);

	    	//cout<<"thread function\n";
	    	if(app)
	    		ofRunApp(app);
	    	stop();
	        while(isThreadRunning())
	        {
	            // Attempt to lock the mutex.  If blocking is turned on,
	            if(lock())
	            {
	               
	            }
	            else
	            {
	                // If we reach this else statement, it means that we could not
	                // lock our mutex, and so we do not need to call unlock().
	                // Calling unlock without locking will lead to problems.
	                ofLogWarning("threadedFunction()") << "Unable to lock mutex.";
	            }
	        }
	    }
	//protected:
};

#endif