#include "mapParse.h"

MapParse::MapParse()
{
    maps=new Map[getMaxSize()];
}

MapParse::~MapParse()
{
    delete maps;
    maps=nullptr;
}


void MapParse::reset()
{
	//delete maps;
	//maps=nullptr;
	//maps=new Map[getMaxSize()];
	//setSize(0);
}

void MapParse::readDelimiter(vector<string>& split)
{
	for(size_t i=0;i<split.size();++i)//add info to map
    {
        if(i==0)//index
            continue;
        else
        {
            vector<string>sub_split;
            Split::splitString(split.at(i),sub_split,getSubDelimiter());

            if(i==1)//dimensions
            {
                maps[getSize()].setWidth(Functions::strToInt(sub_split.at(0)));
                maps[getSize()].setHeight(Functions::strToInt(sub_split.at(1)));
            }
            else if(i==2)//start
            {
                maps[getSize()].setStartX(Functions::strToInt(sub_split.at(0)));
                maps[getSize()].setStartY(Functions::strToInt(sub_split.at(1)));
            }
            else if(i==3)//goal
            {
                maps[getSize()].setGoalX(Functions::strToInt(sub_split.at(0)));
                maps[getSize()].setGoalY(Functions::strToInt(sub_split.at(1)));
            }
            else//barriers
            {
                int sizeSub=sub_split.size();
                int *temp=new int[sizeSub];

                for(int j=0;j<sizeSub;++j)
                    temp[j]=Functions::strToInt(sub_split.at(j));


                maps[getSize()].addBarrier(temp,sizeSub);

                //delete temp;
            }
        }
    }
	maps[getSize()].initializeMap();
}


void MapParse::increase()
{

    Map* temp=new Map[getMaxSize()];

    for(int i=0;i<getSize();++i)
        temp[i]=maps[i];

    delete[] maps;


    setMaxSize(getMaxSize()*2);
    maps=new Map[getMaxSize()];

    for(int i=0;i<getSize();++i)
        maps[i]=temp[i];

    delete[] temp;

    //temp=nullptr;

}

void MapParse::get(int i,Map*& m)
{
    cout<<i<<endl;
    if(i<0 || i>=getSize())
    {
        m=nullptr;
        return;
    }
    m=&maps[i];
}

void MapParse::get(Map*& m)
{
    m=maps;
}
