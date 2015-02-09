/*

        CCCCCCCCCCCCC   SSSSSSSSSSSSSSS PPPPPPPPPPPPPPPPP
     CCC::::::::::::C SS:::::::::::::::SP::::::::::::::::P
   CC:::::::::::::::CS:::::SSSSSS::::::SP::::::PPPPPP:::::P
  C:::::CCCCCCCC::::CS:::::S     SSSSSSSPP:::::P     P:::::P
 C:::::C       CCCCCCS:::::S              P::::P     P:::::P
C:::::C              S:::::S              P::::P     P:::::P
C:::::C               S::::SSSS           P::::PPPPPP:::::P
C:::::C                SS::::::SSSSS      P:::::::::::::PP
C:::::C                  SSS::::::::SS    P::::PPPPPPPPP
C:::::C                     SSSSSS::::S   P::::P
C:::::C                          S:::::S  P::::P
 C:::::C       CCCCCC            S:::::S  P::::P
  C:::::CCCCCCCC::::CSSSSSSS     S:::::SPP::::::PP
   CC:::::::::::::::CS::::::SSSSSS:::::SP::::::::P
     CCC::::::::::::CS:::::::::::::::SS P::::::::P
        CCCCCCCCCCCCC SSSSSSSSSSSSSSS   PPPPPPPPPP
 */

#ifndef CSP_H
#define CSP_H

#include "constraint.h"
#include "reviseNode.h"


#include <list>

using namespace std;

template <class T>//for value stored in constraint
class CSP
{
	private:
		vector<Constraint<T> *> constraints;




		list<ReviseNode<T>*> queue;

		bool valueExistsInDomain(const string&,T,int);//variable,domain value,constraint pos
		bool posExistsInDomain(const string&,int,int);

		bool removeFromDomain(ReviseNode<T>*);//removes value from domain saved in reviseNode

	protected:
		void init();//fill up queue with all value pairs
		bool revise(const string &,int,int);//variable, domain pos,constraint pos (index)
		bool revise(ReviseNode<T>*);

	public:
		CSP();

		 void addConstraint(Constraint<T>&);

		bool domainFilter();

		bool isQueueEmpty();

		bool rerun(ReviseNode<T>*);

		list<ReviseNode<T>*> *getQueue();

		void addQueue(Constraint<T>&);
		void printQueue();

		void printOriginalConstraints();



};
#include "csp.cpp"
#endif
