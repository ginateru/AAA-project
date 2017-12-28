
#ifndef __CLASS_H__
#define __CLASS_H__

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;


//////////////////////////////////////////////////����� ��������/////////////////////////////////////////////////////////////////
class Entity {
public:
	enum { left, right, up, down, stay} state;// ��� ������������ - ��������� �������
	float dx, dy, x, y, speed, moveTimer;//�������� ���������� ������ ��� ������� �����
	int w, h, health, score; //���������� �health�, �������� ����� ������
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








#endif // __PCLASS_H__