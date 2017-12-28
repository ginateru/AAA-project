#include "EnemyClass.h"
#include "map.h"
Enemy::Enemy(Image &image, float X, float Y, int W, int H, std::string Name) :Entity(image, X, Y, W, H, Name)
{
	if (name == "Enemy")
	{
		sprite.setTextureRect(IntRect(0, 0, w, h));
		direction = rand() % (4); 
		speed = 0.1;
		dx = speed;
	}
};

void Enemy::checkCollisionWithMap(double Dx, double Dy)//ф-ци€ проверки столкновений с картой
{
		for (int i = y / 47; i < (y + h) / 47; i++)//проходимс€ по элементам карты
			for (int j = x / 47; j<(x + w) / 47; j++)
			{
				if ((TileMap[i][j] == '0') || (TileMap[i][j] == '1'))//если элемент - тайлик земли
				{
					if (Dy > 0) {
						y = i * 47 - h;  dy = -0.1; 
						direction = rand() % (4); //Ќаправление движени€ врага
						}//по Y 
					if (Dy < 0) {
						y = i * 47 + 47; dy = 0.1; 
						direction = rand() % (4);//Ќаправление движени€ врага 
						}//столкновение с верхними кра€ми 
					if (Dx > 0) {
						x = j * 47 - w; dx = -0.1; 
						direction = rand() % (4);//Ќаправление движени€ врага 
						}//с правым краем карты
					if (Dx < 0) {
						x = j * 47 + 47; dx = 0.1; 
						direction = rand() % (4); //Ќаправление движени€ врага
						}// с левым краем карты
				}
			}
	}


void Enemy::update(float time)
	{
		if (life) {

		switch (direction)//делаютс€ различные действи€ в зависимости от состо€ни€
		{
		case 0:{//состо€ние идти вправо
		dx = speed;
		dy = 0;
		sprite.setTextureRect(IntRect(160, 0, 40, 47));
		break;
		}
		case 1:{//состо€ние идти влево
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

		x += dx*time; //движение по УXФ
		checkCollisionWithMap(dx, 0);//обрабатываем столкновение по ’

		y += dy*time; //движение по УYФ
		checkCollisionWithMap(0, dy);//обрабатываем столкновение по Y

		sprite.setPosition(x, y);

		if (health <= 0){ life = false; }//если жизней меньше 0, либо равно 0, то умираем
		
	}
};

