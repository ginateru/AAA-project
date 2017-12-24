
#ifndef __PCLASS_H__
#define __PCLASS_H__

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

class Player // ����� ������
{ 
	public:
		float x, y, w, h, dx, dy, speed ; //���������� ������ � � �, ������ ������, ��������� (�� � � �� �), ���� ��������
		int dir ; //����������� (direction) �������� ������
		String File; //���� � �����������
		Image image;//���� �����������
		Texture texture;//���� ��������
		Sprite sprite;//���� ������

		Player(String F, float X, float Y, float W, float H);	//����������� � �����������(�����������) ��� ������ Player. 
														//��� �������� ������� ������ �� ����� �������� ��� �����, 
														//���������� � � �, ������ � ������ 


		void update(float time); //������� "���������" ������� ������. update - ����������. ��������� � ���� ����� SFML , ���������� ���� �������� ����������, ����� ��������� ��������.
	
};
#endif // __PCLASS_H__