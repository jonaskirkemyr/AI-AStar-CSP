#ifndef FILEPARSE_H
#define FILEPARSE_H


#include <iostream>
#include <fstream>

#include "StringSplit.h"
#include "../map.h"
#include "cspGraph.h"



using namespace std;

class FileParse
{
        

    protected:
        virtual void increase()=0;
        bool isFileOpen();
        void init();


        ifstream *file;

        int adderSize; 
        int maxSize;

    
        string delimiter;
        string subDelimiter;
        virtual void readDelimiter(vector<string>&)=0;

		virtual void reset()=0;



    public:
        FileParse(int=10);//map max size
        
        virtual ~FileParse();

        bool openFile(string);
        bool readFile();

        const string &getDelimiter() const;
        const string &getSubDelimiter() const;

        void setDelimiter(const string&);
        void setSubDelimiter(const string&);

        int getSize();
        int getMaxSize();

		void setSize(int);

        void setMaxSize(int);


        
        virtual void get(int i,Map*& m){return;}//mapParse
        virtual void get(Map*& m){return;}


        virtual void get(int i,CSPGraph*& s){return;}//equation parse
        virtual void get(CSPGraph*& s){return;}
    






};



#endif // FILEPARSE_H
