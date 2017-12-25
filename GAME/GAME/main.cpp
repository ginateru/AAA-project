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
	heroImage.loadFromFile("images/blue_dude.png"); // ��������� ����������� ������
	
	Player p(heroImage,0, 250, 52, 47,"Player1");

	Image map_image;//������ ����������� ��� �����
	map_image.loadFromFile("images/map.png");//��������� ���� ��� �����
	Texture map;//�������� �����
	map.loadFromImage(map_image);//�������� �������� ���������
	Sprite s_map;//������ ������ ��� �����
	s_map.setTexture(map);//�������� �������� ��������

	Clock clock;
	Clock gameTimeClock;//���������� �������� �������, ����� ����� ������� ����� ���� 
	int gameTime = 0;//�������� ������� �����, ����������������.

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

								////////////////////////////////////////////////////////////////////////
	

		p.update(time);




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

void Player::checkCollisionWithMap(float Dx, float Dy)	
	{
	for (int i = y / 47; i < (y + h) / 47; i++)//���������� �� ��������� �����
		for (int j = x / 47; j<(x + w) / 47; j++)
		{
			if (TileMap[i][j] == '0')//���� ������� ������ �����
			{
			if (Dy > 0) { y = i * 47 - h;  dy = 0; }//�� Y 
			if (Dy < 0) { y = i * 47 + 47; dy = 0; }//������������ � �������� ������ 
			if (Dx > 0) { x = j * 47 - w; dx = 0; }//� ������ ����� �����
			if (Dx < 0) { x = j * 47 + 47; dx = 0; }// � ����� ����� �����
			}
				
		}
	}