#include "BulletClass.h"
#include "map.h"

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
void Bullet::update(float time)
	{
		
		switch (direction)
		{
		case 0: dx = -speed; dy = 0;  break;
		case 1: dx = speed; dy = 0;   break;
		case 2: dx = 0; dy = -speed;  break;
		case 3: dx = 0; dy = speed;   break;
		case 4: dx = 0; dy = 0; break;
		}

		if (life)
		{
			x += dx*time;
			y += dy*time;

		


			for (int i =y / 47; i < (y + h) / 47; i++)
				for (int j = x / 47; j < (x + w) / 47; j++)
				{
					if ((TileMap[i][j] == '0') || (TileMap[i][j] == '1'))
				
					life = false;
					
				}
				sprite.setPosition(x + w / 2, y + h /2);
				
		}
	
  }
  
