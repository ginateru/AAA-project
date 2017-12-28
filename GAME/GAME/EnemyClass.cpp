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

void Enemy::checkCollisionWithMap(double Dx, double Dy)//�-��� �������� ������������ � ������
{
		for (int i = y / 47; i < (y + h) / 47; i++)//���������� �� ��������� �����
			for (int j = x / 47; j<(x + w) / 47; j++)
			{
				if ((TileMap[i][j] == '0') || (TileMap[i][j] == '1'))//���� ������� - ������ �����
				{
					if (Dy > 0) {
						y = i * 47 - h;  dy = -0.1; 
						direction = rand() % (4); //����������� �������� �����
						}//�� Y 
					if (Dy < 0) {
						y = i * 47 + 47; dy = 0.1; 
						direction = rand() % (4);//����������� �������� ����� 
						}//������������ � �������� ������ 
					if (Dx > 0) {
						x = j * 47 - w; dx = -0.1; 
						direction = rand() % (4);//����������� �������� ����� 
						}//� ������ ����� �����
					if (Dx < 0) {
						x = j * 47 + 47; dx = 0.1; 
						direction = rand() % (4); //����������� �������� �����
						}// � ����� ����� �����
				}
			}
	}


void Enemy::update(float time)
	{
		if (life) {

		switch (direction)//�������� ��������� �������� � ����������� �� ���������
		{
		case 0:{//��������� ���� ������
		dx = speed;
		dy = 0;
		sprite.setTextureRect(IntRect(160, 0, 40, 47));
		break;
		}
		case 1:{//��������� ���� �����
		dx = -speed;
		dy = 0;
		sprite.setTextureRect(IntRect(112, 0, 40, 47));
		break;
		}
		case 2:{//���� �����
		dy = -speed;
		dx = 0;
		sprite.setTextureRect(IntRect(56, 0, 56, 47));
		break;
		}
		case 3:{//���� ����
		dy = speed;
		dx = 0;
		sprite.setTextureRect(IntRect(0, 0, w, h));
		break;
		}
		}

		x += dx*time; //�������� �� �X�
		checkCollisionWithMap(dx, 0);//������������ ������������ �� �

		y += dy*time; //�������� �� �Y�
		checkCollisionWithMap(0, dy);//������������ ������������ �� Y

		sprite.setPosition(x, y);

		if (health <= 0){ life = false; }//���� ������ ������ 0, ���� ����� 0, �� �������
		
	}
};

