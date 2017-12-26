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

