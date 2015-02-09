#include "square.h"

/** BRIGHT
.#####...#####...######..##..##...####...######..######.
.##..##..##..##....##....##..##..##..##....##....##.....
.#####...#####.....##....##..##..######....##....####...
.##......##..##....##.....####...##..##....##....##.....
.##......##..##..######....##....##..##....##....######.
........................................................
**/

void Square::initPos()
{
	x_pos=0;
	y_pos=0;
}

void Square::initColor()
{
	color=new ofColor(0,0,0);//black as stand color
}

void Square::initWH()
{
	width=Settings::S_WIDTH;
	height=Settings::S_HEIGHT;
}




/**
.#####...##..##..#####...##......######...####..
.##..##..##..##..##..##..##........##....##..##.
.#####...##..##..#####...##........##....##.....
.##......##..##..##..##..##........##....##..##.
.##.......####...#####...######..######...####..
................................................
**/
Square::Square()
{
	initPos();
	initColor();
	initWH();


}

Square::Square(ofColor &color)
{
	initPos();
	initWH();

   // this->color=new ofColor();
	this->color=&color;//points to color
}


Square::Square(float x,float y,float w,float h)
{
	x_pos=x;
	y_pos=y;

	width=w;
	height=h;
}

Square::Square(const Square & copy)
{
	x_pos=copy.x_pos; 
	y_pos=copy.y_pos;

	width=copy.width;
	height=copy.height;

	delete color;
	color=new ofColor();
	color->set(copy.color->r,copy.color->g,copy.color->b);
}

Square::~Square()
{
	delete color;
	color=nullptr;
}






void Square::setColor(const ofColor& set)
{
	delete color;
	color=new ofColor();
	*color=set;
}

const ofColor *Square::getColor(){return color;}


void Square::setXPos(float x){x_pos=x;}
float Square::getXPos(){return x_pos;}

void Square::setYPos(float y){y_pos=y;}
float Square::getYPos(){return y_pos;}

void Square::setWidth(float width)
{
	this->width=width;
}

void Square::setHeight(float height)
{
	this->height=height;
}

float Square::getWidth(){return width;}
float Square::getHeight(){return height;}


void Square::draw()
{
	ofSetColor(*color);
	ofRect(x_pos,y_pos,width,height);
	
}

void Square::drawWithColor(const ofColor& c)
{
	ofSetColor(c);
	ofRect(x_pos,y_pos,width,height);
}
