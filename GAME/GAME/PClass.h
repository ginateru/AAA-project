#include "Class.h"
//////////////////////////////////////////////////����� �����/////////////////////////////////////////////////////////////////////
class Player :public Entity {
public:
	bool NoWin;
	Player(Image &image, float X, float Y, int W, int H, std::string Name);
	
	void control();

	void Player::checkCollisionWithMap(float Dx, float Dy);		//����� �������� ������������ � ���������� �����

	void update(float time);								//����� "���������/����������" ������� ������.
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////