/** doh



   SSSSSSSSSSSSSSS
 SS:::::::::::::::S
S:::::SSSSSS::::::S
S:::::S     SSSSSSS
S:::::S               qqqqqqqqq   qqqqquuuuuu    uuuuuu    aaaaaaaaaaaaa  rrrrr   rrrrrrrrr       eeeeeeeeeeee
S:::::S              q:::::::::qqq::::qu::::u    u::::u    a::::::::::::a r::::rrr:::::::::r    ee::::::::::::ee
 S::::SSSS          q:::::::::::::::::qu::::u    u::::u    aaaaaaaaa:::::ar:::::::::::::::::r  e::::::eeeee:::::ee
  SS::::::SSSSS    q::::::qqqqq::::::qqu::::u    u::::u             a::::arr::::::rrrrr::::::re::::::e     e:::::e
    SSS::::::::SS  q:::::q     q:::::q u::::u    u::::u      aaaaaaa:::::a r:::::r     r:::::re:::::::eeeee::::::e
       SSSSSS::::S q:::::q     q:::::q u::::u    u::::u    aa::::::::::::a r:::::r     rrrrrrre:::::::::::::::::e
            S:::::Sq:::::q     q:::::q u::::u    u::::u   a::::aaaa::::::a r:::::r            e::::::eeeeeeeeeee
            S:::::Sq::::::q    q:::::q u:::::uuuu:::::u  a::::a    a:::::a r:::::r            e:::::::e
SSSSSSS     S:::::Sq:::::::qqqqq:::::q u:::::::::::::::uua::::a    a:::::a r:::::r            e::::::::e
S::::::SSSSSS:::::S q::::::::::::::::q  u:::::::::::::::ua:::::aaaa::::::a r:::::r             e::::::::eeeeeeee
S:::::::::::::::SS   qq::::::::::::::q   uu::::::::uu:::u a::::::::::aa:::ar:::::r              ee:::::::::::::e
 SSSSSSSSSSSSSSS       qqqqqqqq::::::q     uuuuuuuu  uuuu  aaaaaaaaaa  aaaarrrrrrr                eeeeeeeeeeeeee
                               q:::::q
                               q:::::q
                              q:::::::q
                              q:::::::q
                              q:::::::q
                              qqqqqqqqq


**/





#ifndef SQUARE_H
#define SQUARE_H



#include "../settings/settings.h"

#include "ofColor.h"
#include "ofGraphics.h"

class Square
{
	private:
		ofColor *color;//pointer to color obj (when it's pointed to a color, if it's changed, the color of the shape changes as well)

		//position
		float x_pos,y_pos;

		//width and height of rect
		float width,height;


		//initializers
		void initPos();
		void initColor();
		void initWH();


	public:
		Square();
		Square(ofColor&);
		Square(float,float,float=Settings::S_WIDTH,float=Settings::S_HEIGHT);//x,y,w,h

		Square(const Square&);//copy const
		~Square();//destructor

		void setColor(const ofColor&);
		const ofColor *getColor();

		void setXPos(float);
		float getXPos();

		void setYPos(float);
		float getYPos();

		void setWidth(float);
		void setHeight(float);

		float getWidth();
		float getHeight();


		void draw();
		void drawWithColor(const ofColor&);


};



#endif
