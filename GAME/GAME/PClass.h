
#ifndef __PCLASS_H__
#define __PCLASS_H__

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

class Player // класс Игрока
{ 
	public:
		float x, y, w, h, dx, dy, speed ; //координаты игрока х и у, высота ширина, ускорение (по х и по у), сама скорость
		int dir ; //направление (direction) движения игрока
		String File; //файл с расширением
		Image image;//сфмл изображение
		Texture texture;//сфмл текстура
		Sprite sprite;//сфмл спрайт

		Player(String F, float X, float Y, float W, float H);	//Конструктор с параметрами(формальными) для класса Player. 
														//При создании объекта класса мы будем задавать имя файла, 
														//координату Х и У, ширину и высоту 


		void update(float time); //функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
	
};
#endif // __PCLASS_H__