#include "Class.h"

Enemy::Enemy(Image &image, float X, float Y, int W, int H, std::string Name) :Entity(image, X, Y, W, H, Name)
{
	if (name == "Enemy")
	{
		sprite.setTextureRect(IntRect(0, 0, w, h));
		direction = rand() % (3); 
		speed = 0.1;
		dx = speed;
	}
};


void Enemy::update(float time)
	{
		if (life) {

		switch (direction)//делаются различные действия в зависимости от состояния
		{
		case 0:{//состояние идти вправо
		dx = speed;
		dy = 0;
		sprite.setTextureRect(IntRect(160, 0, 40, 47));
		break;
		}
		case 1:{//состояние идти влево
		dx = -speed;
		dy = 0;
		sprite.setTextureRect(IntRect(112, 0, 40, 47));
		break;
		}
		case 2:{//идти вверх
		dy = -speed;
		dx = 0;
		sprite.setTextureRect(IntRect(56, 0, 56, 47));
		break;
		}
		case 3:{//идти вниз
		dy = speed;
		dx = 0;
		sprite.setTextureRect(IntRect(0, 0, w, h));
		break;
		}
		}

		x += dx*time; //движение по “X”
		checkCollisionWithMap(dx, 0);//обрабатываем столкновение по Х

		y += dy*time; //движение по “Y”
		checkCollisionWithMap(0, dy);//обрабатываем столкновение по Y

		sprite.setPosition(x, y);

		if (health <= 0){ life = false; }//если жизней меньше 0, либо равно 0, то умираем
		
	}
};

