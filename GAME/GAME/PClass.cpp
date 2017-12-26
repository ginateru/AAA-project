#include "Class.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Player::Player(Image &image, float X, float Y, int W, int H, std::string Name) :Entity(image, X, Y, W, H, Name)
	{
 
		state = stay;
		if (name == "Player1")
		{
			//Задаем спрайту один прямоугольник для
			//вывода одного игрока. IntRect – для приведения типов
			sprite.setTextureRect(IntRect(0, 0, w, h));
		}
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Player::control(){
		if (Keyboard::isKeyPressed(Keyboard::A)) {
			sprite.setTextureRect(IntRect(112, 0, 40, 47));
			state = left;
			speed = 0.1;
		}


		if (Keyboard::isKeyPressed(Keyboard::D)) {
			sprite.setTextureRect(IntRect(160, 0, 40, 47));
			state = right;
			speed = 0.1;
		}



		if (Keyboard::isKeyPressed(Keyboard::W)) {
			sprite.setTextureRect(IntRect(56, 0, 56, 47));
			state = up;
			speed = 0.1;
		}
		
		if (Keyboard::isKeyPressed(Keyboard::S)) {
			sprite.setTextureRect(IntRect(0, 0, w, h));
			state = down;
			speed = 0.1;
		}
	}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Player::update(float time) //метод "оживления/обновления" объекта класса.
	{
	if (life) {//проверяем, жив ли герой
		control();//функция управления персонажем
		switch (state)//делаются различные действия в зависимости от состояния
		{
		case right:{//состояние идти вправо
			dx = speed;
			dy = 0;
				break;
		}
		case left:{//состояние идти влево
				dx = -speed;
				dy = 0;
				break;
			}
		case up:{//идти вверх
			dy = -speed;
			dx = 0;
				break;
			}
			case down:{//идти вниз
				dy = speed;
				dx = 0;
				break;
			}
			case stay:{//стоим
				dy = speed;
				dx = speed;
				break;
			}
			}

			x += dx*time; //движение по “X”
			checkCollisionWithMap(dx, 0);//обрабатываем столкновение по Х
			y += dy*time; //движение по “Y”
			checkCollisionWithMap(0, dy);//обрабатываем столкновение по Y

			speed = 0;    //обнуляем скорость, чтобы персонаж остановился.

			sprite.setPosition(x, y); //спрайт в позиции (x, y).

		if (health <= 0){ life = false; }//если жизней меньше 0, либо равно 0, то умираем 
		}
	}
