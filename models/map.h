#ifndef MAP_H
#define MAP_H

//typedef int barrier[4];//x,y,w,h

#include <vector>
#include <iostream>

#include "../settings/settings.h"
using namespace std;

class Map
{
    private:
        //dimensions of board
        int width;
        int height;

        //start pos
        int start_x;
        int start_y;

        //goal pos
        int goal_x;
        int goal_y;

        vector<int*>barriers;//x,y,w,h

        int **search_map;

        bool initialized;

        void initMap();
        void createMap();


    public:
        Map();
        Map(const Map&);
        ~Map();

        //SET
        void setWidth(int);
        void setHeight(int);

        void setStartX(int);
        void setStartY(int);

        void setGoalX(int);
        void setGoalY(int);

        void addBarrier(int*,int=4);

        //GET
        int getWidth();
        int getHeight();

        int getStartX();
        int getStartY();

        int getGoalX();
        int getGoalY();

        const vector<int*>& getBarriers() const;

        const int* getBarrierAt(int=0) const;


        bool initializeMap();
        int **getMap();
        void printMap();


};
#endif // MAP_H
