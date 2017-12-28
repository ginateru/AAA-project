
#ifndef __CLASS_H__
#define __CLASS_H__

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;


////////////////////////////////////////////////// ласс —ущность/////////////////////////////////////////////////////////////////
class Entity {
public:
	enum { left, right, up, down, stay} state;// тип перечислени€ - состо€ние объекта
	float dx, dy, x, y, speed, moveTimer;//добавили переменную таймер дл€ будущих целей
	int w, h, health, score; //переменна€ УhealthФ, хран€ща€ жизни игрока
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








#endif // __PCLASS_H__