#include "map.h"

void Map::initMap()
{
    search_map=new int*[height];
    for(int i=0;i<height;++i)
        search_map[i]=new int[width];

    for(int i=0;i<height;++i)
        for(int j=0;j<width;++j)
            search_map[i][j]=Settings::OPEN;
}

 
void Map::createMap()
{

    search_map[start_y][start_x]    =   Settings::START_POS;
    search_map[goal_y][goal_x]      =   Settings::GOAL_POS;

    for(size_t i=0;i<barriers.size();++i)//add obstacles to map
    { 
        int * temp=barriers.at(i);
        search_map[temp[1]][temp[0]]=Settings::OBSTACLE;//0=x,1=y

        for(int j=temp[1];j<(temp[1]+temp[3]);++j)//width
            for(int k=temp[0];k<(temp[0]+temp[2]);++k)//height
                search_map[j][k]=Settings::OBSTACLE;
    }
}


Map::Map()//size of barriers
{
    width=Settings::NOT_INIT;
    height=Settings::NOT_INIT;

    start_x=Settings::NOT_INIT;
    start_y=Settings::NOT_INIT;

    goal_x=Settings::NOT_INIT;
    goal_y=Settings::NOT_INIT;

    initialized=false;

    //search_map=new int*[10];

    //barriers=new barrier[maxSize];
}

Map::Map(const Map& copy)
{
    width=copy.width;
    height=copy.height;

    start_x=copy.start_x;
    start_y=copy.start_y;

    goal_x=copy.goal_x;
    goal_y=copy.goal_y;

    initialized=copy.initialized;

    for(size_t i=0;i<copy.barriers.size();++i)
        barriers[i]=copy.barriers.at(i);

    initMap();
    createMap();

}




Map::~Map()
{
    for(int i=0;i<height;++i)
        delete[] search_map[i];
    delete[] search_map;
    search_map=nullptr;

   // for(size_t i=0;i<barriers.size();++i)
   //     delete barriers.at(i);
}




//SET
void Map::setWidth(int w)
{
    width=w;
}
void Map::setHeight(int h)
{
    height=h;
}

void Map::setStartX(int x)
{
    start_x=x;
}
void Map::setStartY(int y)
{
    start_y=y;
}

void Map::setGoalX(int x)
{
    goal_x=x;
}
void Map::setGoalY(int y)
{
    goal_y=y;
}

void Map::addBarrier(int *b,int sizeB)
{
    int *temp=new int;
    temp=b;
    barriers.push_back(temp);
}

//GET

int Map::getWidth()
{
    return width;
}
int Map::getHeight()
{
    return height;
}

int Map::getStartX()
{
    return start_x;
}
int Map::getStartY()
{
    return start_y;
}

int Map::getGoalX()
{
    return goal_x;
}
int Map::getGoalY()
{
    return goal_y;
}

const vector<int*>& Map::getBarriers() const
{
    return barriers;
}

const int* Map::getBarrierAt(int i) const
{
    if((size_t)i<0 || (size_t)i>barriers.size())
        return nullptr;
    return barriers.at(i);
}


bool Map::initializeMap()
{
     if(width==Settings::NOT_INIT || height==Settings::NOT_INIT ||
       start_x==Settings::NOT_INIT || start_y==Settings::NOT_INIT ||
       goal_x==Settings::NOT_INIT || goal_y==Settings::NOT_INIT)
        return false;

    initMap();
    createMap();

    initialized=true;

    return true;
}

int ** Map::getMap()
{
    if(!initialized)
        if(!initializeMap())
            return nullptr;

    return search_map;

}

void Map::printMap()
{
    if(!initialized)
        if(!initializeMap())
            return;

    for(int i=0;i<height;++i)
    {
        for(int j=0;j<width;++j)
            cout<<search_map[i][j]<<" ";
        cout<<endl;
    }
}
