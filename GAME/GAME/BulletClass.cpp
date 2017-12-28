#include "Class.h"

Bullet::Bullet(Image &image, float X, float Y, int W, int H, std::string  Name, int dir) :Entity(image, X, Y, W, H, Name)
	{
		if (name == "Bullet")
		{

			sprite.setTextureRect(IntRect(0, 0, w, h));
		    x = X;
	     	y = Y;
		    direction = dir;
		    speed = 0.15;
    		w = h = 20;
	    	life = true;
	}
}

  
