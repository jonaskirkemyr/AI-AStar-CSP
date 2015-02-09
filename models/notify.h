#ifndef NOTIFY_H
#define NOTIFY_H

#include <vector>
#include <algorithm> //used for std::find :)
#include "listener.h"
using namespace std;

class Notify
{

	private:
		vector<Listener*> listeners;

	protected:
		virtual void tell();

	public:
		virtual void addListener(Listener*);
		virtual void removeListener(Listener*);
};



#endif
