#include <SFML/Graphics.hpp>
#include <iostream> 
#include "Class.h"
#include "map.h"

using namespace sf;


int main()
{

	VideoMode desktop = sf::VideoMode::getDesktopMode();
	RenderWindow window(sf::VideoMode(800, 600, desktop.bitsPerPixel), "test");

	Image heroImage;
	heroImage.loadFromFile("images/blue_dude.png"); // загружаем изображение игрока
	
	Player p(heroImage,0, 250, 52, 47,"Player1");

	Image map_image;//объект изображения для карты
	map_image.loadFromFile("images/map.png");//загружаем файл для карты
	Texture map;//текстура карты
	map.loadFromImage(map_image);//заряжаем текстуру картинкой
	Sprite s_map;//создаём спрайт для карты
	s_map.setTexture(map);//заливаем текстуру спрайтом

	Clock clock;
	Clock gameTimeClock;//переменная игрового времени, будем здесь хранить время игры 
	int gameTime = 0;//объявили игровое время, инициализировали.

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	while (window.isOpen())	
	{
		float time = clock.getElapsedTime().asMicroseconds(); 
		clock.restart(); //перезагружает время
		time = time/650;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

								////////////////////////////////////////////////////////////////////////
	

		p.update(time);




		window.clear();

		for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			if (TileMap[i][j] == ' ') s_map.setTextureRect(IntRect(0, 0, 47, 47)); //если встретили символ пробел, то рисуем 1й квадратик
			if (TileMap[i][j] == '0') s_map.setTextureRect(IntRect (47, 0, 47, 47));//если встретили символ 0, то рисуем 2й квадратик
 
 
			s_map.setPosition(j * 47, i * 47);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат
 
			window.draw(s_map);//рисуем квадратики на экран
		}


		window.draw(p.sprite);
		window.display();
	}

        
return 0;
}

void Player::checkCollisionWithMap(float Dx, float Dy)	
	{
	for (int i = y / 47; i < (y + h) / 47; i++)//проходимся по элементам карты
		for (int j = x / 47; j<(x + w) / 47; j++)
		{
			if (TileMap[i][j] == '0')//если элемент тайлик земли
			{
			if (Dy > 0) { y = i * 47 - h;  dy = 0; }//по Y 
			if (Dy < 0) { y = i * 47 + 47; dy = 0; }//столкновение с верхними краями 
			if (Dx > 0) { x = j * 47 - w; dx = 0; }//с правым краем карты
			if (Dx < 0) { x = j * 47 + 47; dx = 0; }// с левым краем карты
			}
				
		}
	}