#include <SFML/Graphics.hpp>
#include <iostream> 
#include "map.h"
#include "PClass.h"

using namespace sf;

int main()
{
    

	Clock clock;

	VideoMode desktop = sf::VideoMode::getDesktopMode();
	RenderWindow window(sf::VideoMode(800, 600, desktop.bitsPerPixel), "test");

	Player p("blue_dude.png",0, 250, 52, 47);

	Image map_image;//������ ����������� ��� �����
	map_image.loadFromFile("images/map.png");//��������� ���� ��� �����
	Texture map;//�������� �����
	map.loadFromImage(map_image);//�������� �������� ���������
	Sprite s_map;//������ ������ ��� �����
	s_map.setTexture(map);//�������� �������� ��������

	while (window.isOpen())	
	{
		float time = clock.getElapsedTime().asMicroseconds(); 
		clock.restart(); //������������� �����
		time = time/650;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


	

		if ((Keyboard::isKeyPressed(Keyboard::Left)||(Keyboard::isKeyPressed(Keyboard::A)))) { 
	   p.sprite.move(-0.1*time, 0); p.sprite.setTextureRect(IntRect(111, 0, 42, 47)); 
		} 
		if ((Keyboard::isKeyPressed(Keyboard::Right)||(Keyboard::isKeyPressed(Keyboard::D)))) {
	   p.sprite.move(0.1*time, 0); p.sprite.setTextureRect(IntRect(160, 0, 42, 47)); 
		} 
		if ((Keyboard::isKeyPressed(Keyboard::Up)||(Keyboard::isKeyPressed(Keyboard::W)))) { 
	  p.sprite.move(0, -0.1*time); p.sprite.setTextureRect(IntRect(56, 0, 52, 47)); 
		}
		if ((Keyboard::isKeyPressed(Keyboard::Down)||(Keyboard::isKeyPressed(Keyboard::S)))) {
	   p.sprite.move(0, 0.1*time); p.sprite.setTextureRect(IntRect(0, 0, 52, 47)); 
		}




		window.clear();

		for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			if (TileMap[i][j] == ' ') s_map.setTextureRect(IntRect(0, 0, 47, 47)); //���� ��������� ������ ������, �� ������ 1� ���������
			if (TileMap[i][j] == '0') s_map.setTextureRect(IntRect (47, 0, 47, 47));//���� ��������� ������ 0, �� ������ 2� ���������
 
 
			s_map.setPosition(j * 47, i * 47);//�� ���� ����������� ����������, ��������� � �����. �� ���� ������ ������� �� ��� �������. ���� ������, �� ��� ����� ���������� � ����� �������� 32*32 � �� ������ ���� �������
 
			window.draw(s_map);//������ ���������� �� �����
		}


		window.draw(p.sprite);
		window.display();
	}

        
return 0;
}