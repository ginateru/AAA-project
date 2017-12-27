#include "Class.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Player::Player(Image &image, float X, float Y, int W, int H, std::string Name) :Entity(image, X, Y, W, H, Name)
	{
 
		state = stay;
		if (name == "Player1")
		{
			//«адаем спрайту один пр€моугольник дл€
			//вывода одного игрока. IntRect Ц дл€ приведени€ типов
			sprite.setTextureRect(IntRect(0, 0, w, h));
		}
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Player::control(){
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			state = left;
			speed = 0.1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			state = right;
			speed = 0.1;
		}

		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			state = up;
			speed = 0.1;
		}

		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			state = down;
			speed = 0.1;
		}
	}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ћетод проверки столкновений с элементами карты


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Player::update(float time) //метод "оживлени€/обновлени€" объекта класса.
	{
	if (life) {//провер€ем, жив ли герой
		control();//функци€ управлени€ персонажем
		switch (state)//делаютс€ различные действи€ в зависимости от состо€ни€
		{
		case right:{//состо€ние идти вправо
			sprite.setTextureRect(IntRect(160, 0, 39, 47));
			dx = speed;
				break;
		}
		case left:{//состо€ние идти влево
			sprite.setTextureRect(IntRect(111, 0, 42, 47));
				dx = -speed;
				break;
			}
		case up:{//идти вверх
			sprite.setTextureRect(IntRect(56, 0, 52, 47));
			dy = -speed;
				break;
			}
			case down:{//идти вниз
				sprite.setTextureRect(IntRect(0, 0, 52, 47));
				dy = speed;
				break;
			}
			default:{//стоим
				dy = 0;
				dx = 0;
				break;
			}
			}

			x += dx*time; //движение по УXФ
			checkCollisionWithMap(dx, 0);//обрабатываем столкновение по ’
			y += dy*time; //движение по УYФ
			checkCollisionWithMap(0, dy);//обрабатываем столкновение по Y

			speed = 0;    //обнул€ем скорость, чтобы персонаж остановилс€.

			sprite.setPosition(x, y); //спрайт в позиции (x, y).

		if (health <= 0){ life = false; }//если жизней меньше 0, либо равно 0, то умираем 
		}
	}
