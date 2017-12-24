#include "PClass.h"


Player::Player(String F, float X, float Y, float W, float H){  // онструктор с параметрами(формальными) дл€ класса Player. ѕри создании объекта класса мы будем задавать им€ файла, координату ’ и ”, ширину и высоту
		File = F;//им€ файла+расширение
		w = W; h = H;//высота и ширина
		image.loadFromFile("images/" + File);
		image.createMaskFromColor(Color(255, 255, 255)); 
		texture.loadFromImage(image);//закидываем наше изображение в текстуру
		sprite.setTexture(texture);//заливаем спрайт текстурой
		x = 0; y = 250;//координата по€влени€ спрайта
		sprite.setTextureRect(IntRect(0, 0, w, h));  
	}


void Player::update(float time) //функци€ "оживлени€" объекта класса. update - обновление. принимает в себ€ врем€ SFML , вследствие чего работает бесконечно, дава€ персонажу движение.
	{
		switch (dir)//реализуем поведение в зависимости от направлени€. (кажда€ цифра соответствует направлению)
		{
		case 0: dx = speed; dy = 0;   break;
		case 1: dx = -speed; dy = 0;   break;
		case 2: dx = 0; dy = speed;   break;
		case 3: dx = 0; dy = -speed;   break;
		}
 
		x += dx*time;
		y += dy*time;
 
		speed = 0;//занул€ем скорость, чтобы персонаж остановилс€.
		sprite.setPosition(x,y); //выводим спрайт в позицию x y , посередине. бесконечно выводим в этой функции, иначе бы наш спрайт сто€л на месте.
	}