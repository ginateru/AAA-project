#include "PClass.h"
#include "map.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Player::Player(Image &image, float X, float Y, int W, int H, std::string Name) :Entity(image, X, Y, W, H, Name)
	{
 
		state = stay;
		NoWin = true;
		if (name == "Player1")
		{
			//������ ������� ���� ������������� ���
			//������ ������ ������. IntRect � ��� ���������� �����
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
	for (int i = y / 47; i < (y + h) / 47; i++)//���������� �� ��������� �����
		for (int j = x / 47; j<(x + w) / 47; j++)
		{
			if ((TileMap[i][j] == '0') || (TileMap[i][j] == '1'))//���� ������� ������ ����� ��� �������
			{
			if (Dy > 0) { y = i * 47 - h;  dy = 0; }//�� Y 
			if (Dy < 0) { y = i * 47 + 47; dy = 0; }//������������ � �������� ������ 
			if (Dx > 0) { x = j * 47 - w;  dx = 0; }//� ������ ����� �����
			if (Dx < 0) { x = j * 47 + 47; dx = 0; }// � ����� ����� �����
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

void Player::update(float time) //����� "���������/����������" ������� ������.
	{
	if (life && NoWin) {//���������, ��� �� �����
		control();//������� ���������� ����������
		switch (state)//�������� ��������� �������� � ����������� �� ���������
		{
		case right:{//��������� ���� ������
			dx = speed;
			dy = 0;
				break;
		}
		case left:{//��������� ���� �����
				dx = -speed;
				dy = 0;
				break;
			}
		case up:{//���� �����
			dy = -speed;
			dx = 0;
				break;
			}
			case down:{//���� ����
				dy = speed;
				dx = 0;
				break;
			}
			case stay:{//�����
				dy = speed;
				dx = speed;
				break;
			}
			}

			x += dx*time; //�������� �� �X�
			checkCollisionWithMap(dx, 0);//������������ ������������ �� �
			y += dy*time; //�������� �� �Y�
			checkCollisionWithMap(0, dy);//������������ ������������ �� Y

			speed = 0;    //�������� ��������, ����� �������� �����������.

			sprite.setPosition(x, y); //������ � ������� (x, y).

		if (health <= 0){ life = false; }//���� ������ ������ 0, ���� ����� 0, �� ������� 
		}
	}
