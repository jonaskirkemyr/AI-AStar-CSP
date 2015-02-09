#ifndef EQUATIONPARSE_H
#define EQUATIONPARSE_H

#include "fileParse.h"
#include <vector>

#include "../../settings/functions.h"
#include <string>

class EquationParse : public FileParse
{
	private:
		CSPGraph * cspG;

		virtual void reset();

	protected:
		void readDelimiter(vector<string>&);
		void increase();

	public:
		EquationParse();

		void get(int,CSPGraph*&);//equation parse
        void get(CSPGraph*&);



};

#endif
