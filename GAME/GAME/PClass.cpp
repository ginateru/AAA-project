#include "PClass.h"
#include "map.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Player::Player(Image &image, float X, float Y, int W, int H, std::string Name) :Entity(image, X, Y, W, H, Name)
	{
 
		state = stay;
		NoWin = true;
		if (name == "Player1")
		{
			//«адаем спрайту один пр€моугольник дл€
			//вывода одного игрока. IntRect Ц дл€ приведени€ типов
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


void Player::checkCollisionWithMap(float Dx, float Dy)	
	{
	for (int i = y / 47; i < (y + h) / 47; i++)//проходимс€ по элементам карты
		for (int j = x / 47; j<(x + w) / 47; j++)
		{
			if ((TileMap[i][j] == '0') || (TileMap[i][j] == '1'))//если элемент тайлик земли или бамбука
			{
			if (Dy > 0) { y = i * 47 - h;  dy = 0; }//по Y 
			if (Dy < 0) { y = i * 47 + 47; dy = 0; }//столкновение с верхними кра€ми 
			if (Dx > 0) { x = j * 47 - w;  dx = 0; }//с правым краем карты
			if (Dx < 0) { x = j * 47 + 47; dx = 0; }// с левым краем карты
			}
			if (TileMap[i][j] == '2')
			{
	               score++;
				   health+=1;
	               TileMap[i][j] = ' ';
                }
			if (TileMap[i][j] == '3')
			{
				score += 50;
				std::cout << "YOU ARE WINNER!!!";
				TileMap[i][j] = ' ';
				NoWin = false;
			}

			}
				
		}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Player::update(float time) //метод "оживлени€/обновлени€" объекта класса.
	{
	if (life && NoWin) {//провер€ем, жив ли герой
		control();//функци€ управлени€ персонажем
		switch (state)//делаютс€ различные действи€ в зависимости от состо€ни€
		{
		case right:{//состо€ние идти вправо
			dx = speed;
			dy = 0;
				break;
		}
		case left:{//состо€ние идти влево
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

			x += dx*time; //движение по УXФ
			checkCollisionWithMap(dx, 0);//обрабатываем столкновение по ’
			y += dy*time; //движение по УYФ
			checkCollisionWithMap(0, dy);//обрабатываем столкновение по Y

			speed = 0;    //обнул€ем скорость, чтобы персонаж остановилс€.

			sprite.setPosition(x, y); //спрайт в позиции (x, y).

		if (health <= 0){ life = false; }//если жизней меньше 0, либо равно 0, то умираем 
		}
	}
