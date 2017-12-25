#include "Class.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Player::Player(Image &image, float X, float Y, int W, int H, std::string Name) :Entity(image, X, Y, W, H, Name)
	{
 
		state = stay;
		if (name == "Player1")
		{
			//������ ������� ���� ������������� ���
			//������ ������ ������. IntRect � ��� ���������� �����
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
//����� �������� ������������ � ���������� �����
void Player::checkCollisionWithMap(float Dx, float Dy)	
	{
	for (int i = y / 47; i < (y + h) / 47; i++)//���������� �� ��������� �����
		for (int j = x / 47; j<(x + w) / 47; j++)
		{
			if (TileMap[i][j] == '0')//���� ������� ������ �����
			{
			if (Dy > 0) { y = i * 47 - h;  dy = 0; }//�� Y 
			if (Dy < 0) { y = i * 47 + 47; dy = 0; }//������������ � �������� ������ 
			if (Dx > 0) { x = j * 47 - w; dx = 0; }//� ������ ����� �����
			if (Dx < 0) { x = j * 47 + 47; dx = 0; }// � ����� ����� �����
			}
				
		}
	}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Player::update(float time) //����� "���������/����������" ������� ������.
	{
	if (life) {//���������, ��� �� �����
		control();//������� ���������� ����������
		switch (state)//�������� ��������� �������� � ����������� �� ���������
		{
		case right:{//��������� ���� ������
			dx = speed;
				break;
		}
		case left:{//��������� ���� �����
				dx = -speed;
				break;
			}
		case up:{//���� �����
			dy = -speed;
				break;
			}
			case down:{//���� ����
				dy = speed;
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
