
#ifndef __CLASS_H__
#define __CLASS_H__

#include <SFML/Graphics.hpp>
#include <iostream>
#include "map.h"
using namespace sf;


//////////////////////////////////////////////////����� ��������/////////////////////////////////////////////////////////////////
class Entity {
public:
	enum { left, right, up, down, stay} state;// ��� ������������ - ��������� �������
	float dx, dy, x, y, speed, moveTimer;//�������� ���������� ������ ��� ������� �����
	int w, h, health; //���������� �health�, �������� ����� ������
	bool life; //���������� �life� �����, ����������
	Texture texture;//���� ��������
	Sprite sprite;//���� ������ 
	float CurrentFrame;//������ ������� ����
	std::string name;//����� ����� ���� ������, ������ ����� ��������� �� ������
	//������� ����� ���� ���� �������� � update() � ����������� �� �����

	Entity(Image &image, float X, float Y, int W, int H, std::string Name);
	FloatRect getRect();
	virtual void update(float time) = 0;
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////����� �����/////////////////////////////////////////////////////////////////////
class Player :public Entity {
public:

	Player(Image &image, float X, float Y, int W, int H, std::string Name);

	void control();

	void Player::checkCollisionWithMap(float Dx, float Dy);		//����� �������� ������������ � ���������� �����

	void update(float time);								//����� "���������/����������" ������� ������.
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////����� �����////////////////////////////////////////////////////////////////////////
class Enemy :public Entity{
public:
	int direction;//����������� �������� �����
	Enemy(Image &image, float X, float Y, int W, int H, std::string Name);

	void checkCollisionWithMap(float Dx, float Dy);//�-��� �������� ������������ � ������

	void update(float time);
	
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////����� ����//////////////////////////////////////////////////////////////////////

class Bullet :public Entity{//����� ����
public:
	int direction;//����������� ����
	//�� ��� ��, ������ ����� � ����� ��������� ������ (int dir) 
	//��� ������� ����������� ����� ����
	Bullet(Image &image, float X, float Y, int W, int H, std::string  Name, int dir);

	void update(float time);
	
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#endif // __PCLASS_H__