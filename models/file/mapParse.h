#ifndef MAPP_H
#define MAPP_H

#include "../map.h"
#include "../../settings/functions.h"

/**reads a file and parse it into a map
* consistent with the pathFinder class
*
* A file can contain multiple maps
* where each map is represented in one line
*
* structure:
*   index       - number            index of map (used for loading specific map)
*   dimensions  - point (x,y)       dimension of board
*   start       - point (x,y)       position of start node
*   goal        - point (x,y)       position of goal node
*   barriers    - point (x,y,w,h)   position, width & height of barriers. Can contain multiple barriers
*
* example file input:
*   0 10,10 0,0 9,9 2,3,5,5 8,8,2,1
*   1 20,20 0,0 19,19 17,10,2,1 14,4,5,2 3,16,10,2 13,7,5,3 15,15,3,3
**/



#include "../file/fileParse.h"

class MapParse : public FileParse
{

	private:
		Map * maps;

		virtual void reset();

	protected:
		void readDelimiter(vector<string>&);
		void increase();

	public:
		MapParse();
		virtual ~MapParse();

       	void get(int,Map*&);//mapParse
        void get(Map*&);

        

};


#endif
