#ifndef SPLIT_H
#define SPLIT_H

#include <iostream>
#include <vector>
using namespace std;

namespace Split
{
	static void splitString(const string& text,vector<string>& v,const string& delimiter)
	{
		size_t pos=0;
		size_t initPos=0;

		while((pos=(text.find(delimiter,initPos)))!=string::npos)//search for delimiter until end isn't reached
		{
			//string split=text.substr(initPos,pos-initPos+delimiter.length());//get string from initial position to next delimiter position
			string split=text.substr(initPos,pos-initPos);
			v.push_back(split);
			initPos=pos+delimiter.length();//go to position after delimiter found
		}
		//adds last occurance to vector as well
		string split=text.substr(initPos,min(pos,text.size())-initPos);
		v.push_back(split);
	}
}; 

#endif