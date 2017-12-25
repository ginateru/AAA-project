
#ifndef __CLASS_H__
#define __CLASS_H__

#include <SFML/Graphics.hpp>
#include <iostream>
#include "map.h"
using namespace sf;


////////////////////////////////////////////////// ласс —ущность/////////////////////////////////////////////////////////////////
class Entity {
public:
	enum { left, right, up, down, stay} state;// тип перечислени€ - состо€ние объекта
	float dx, dy, x, y, speed, moveTimer;//добавили переменную таймер дл€ будущих целей
	int w, h, health; //переменна€ УhealthФ, хран€ща€ жизни игрока
	bool life; //переменна€ УlifeФ жизнь, логическа€
	Texture texture;//сфмл текстура
	Sprite sprite;//сфмл спрайт 
	float CurrentFrame;//хранит текущий кадр
	std::string name;//враги могут быть разные, врагов можно различать по именам
	//каждому можно дать свое действие в update() в зависимости от имени

	Entity(Image &image, float X, float Y, int W, int H, std::string Name);
	FloatRect getRect();
	virtual void update(float time) = 0;
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////// ласс √ерой/////////////////////////////////////////////////////////////////////
class Player :public Entity {
public:

	Player(Image &image, float X, float Y, int W, int H, std::string Name);

	void control();

	void Player::checkCollisionWithMap(float Dx, float Dy);		//ћетод проверки столкновений с элементами карты

	void update(float time);								//метод "оживлени€/обновлени€" объекта класса.
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////// ласс врага////////////////////////////////////////////////////////////////////////
class Enemy :public Entity{
public:
	int direction;//направление движени€ врага
	Enemy(Image &image, float X, float Y, int W, int H, std::string Name);

	void checkCollisionWithMap(float Dx, float Dy);//ф-ци€ проверки столкновений с картой

	void update(float time);
	
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////// ласс пул€//////////////////////////////////////////////////////////////////////

class Bullet :public Entity{//класс пули
public:
	int direction;//направление пули
	//всЄ так же, только вз€ли в конце состо€ние игрока (int dir) 
	//дл€ задани€ направлени€ полЄта пули
	Bullet(Image &image, float X, float Y, int W, int H, std::string  Name, int dir);

	void update(float time);
	
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#endif // __PCLASS_H__