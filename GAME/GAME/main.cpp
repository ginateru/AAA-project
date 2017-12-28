#include <SFML/Graphics.hpp>
#include <iostream> 
#include "Class.h"
#include "map.h"
#include <sstream>
#include <list>


using namespace sf;


int main()
{
	char t;
	VideoMode desktop = sf::VideoMode::getDesktopMode();
	RenderWindow window(sf::VideoMode(800, 600, desktop.bitsPerPixel), "test");

	Image heroImage;
	Image enemyImage;
	Image BulletImage;
	heroImage.loadFromFile("images/blue_dude.png");
	enemyImage.loadFromFile("images/red_dude.png");
	BulletImage.loadFromFile("images/bullet.png");

	

	Player p(heroImage, 50, 280, 52, 47,"Player1");
	std::list<Entity*>  enemies; 
	std::list<Entity*>  Bullets; 
	std::list<Entity*>::iterator it;
	std::list<Entity*>::iterator no;

	
	const int ENEMY_COUNT = 3;
	int enemiesCount = 0;

	for (int i = 0; i < ENEMY_COUNT; i++)
	{
	float xr = 150 + rand() % 500; //��������� ���������� ����� �� ���� ���� �� ��� �x�
	float yr = 150 + rand() % 350; //��������� ���������� ����� �� ���� ���� �� ��� �y�
		//������� ������ � �������� � ������
		enemies.push_back(new Enemy(enemyImage, xr, yr, 47, 52, "Enemy"));
		enemiesCount += 1; //��������� ������� ������
	}


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
		
		
		if (event.type == sf::Event::KeyPressed)
		{
		if (event.key.code == sf::Keyboard::E)
		{
			
		//��������� � ������ Bullets ����
		Bullets.push_back(new Bullet(BulletImage, p.x, p.y, 20, 20, "Bullet", p.state));
		    
				}
			}
		}


								////////////////////////////////////////////////////////////////////////
	

		p.update(time);
		
		for (it = enemies.begin(); it != enemies.end(); it++)
		{
			(*it)->update(time); //��������� ����� update()
		}


		for (it = Bullets.begin(); it != Bullets.end(); it++)
		{
			
			(*it)->update(time); //��������� ����� update()
			
		}
		if (p.life == true){//���� ����� ���
		for (it = enemies.begin(); it != enemies.end(); it++){//����� �� ������ ������
		if ((p.getRect().intersects((*it)->getRect())) && ((*it)->name == "Enemy"))
				{
					p.health--;
				}
			}
		}
		for (no = Bullets.begin(); no != Bullets.end(); no++)
		{
			for (it = enemies.begin(); it != enemies.end(); it++)
			{
				if((*it)->getRect().intersects((*no)->getRect()))
				{
					(*it)-> life = false;	
					it = enemies.erase(it);
				}
			}
		}


		for (it = Bullets.begin(); it != Bullets.end(); )//������� ��� ���������� �� ������ �� �����
		{// ���� ���� ������ �����, �� ������� ���
			if ((*it)-> life == false)	{ it = Bullets.erase(it); }			
else  
	it++; //� ���� �������� (����������) � ���� �������.
		}




		window.clear();

		for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			if (TileMap[i][j] == ' ') s_map.setTextureRect(IntRect(0, 0, 47, 47)); //���� ��������� ������ ������, �� ������ 1� ���������
			if (TileMap[i][j] == '0') s_map.setTextureRect(IntRect (47, 0, 47, 47));//���� ��������� ������ 0, �� ������ 2� ���������
			if (TileMap[i][j] == '1') s_map.setTextureRect(IntRect (94, 0, 47, 47));
			if (TileMap[i][j] == '2') s_map.setTextureRect(IntRect (141, 0, 47, 47));
			if (TileMap[i][j] == '3') s_map.setTextureRect(IntRect (188, 0, 47, 47));
 
 
			s_map.setPosition(j * 47, i * 47);//�� ���� ����������� ����������, ��������� � �����. �� ���� ������ ������� �� ��� �������. ���� ������, �� ��� ����� ���������� � ����� �������� 32*32 � �� ������ ���� �������
 
			window.draw(s_map);//������ ���������� �� �����
		}
			Font font;//����� 
font.loadFromFile("HANZI.ttf");
Text text("", font, 20);
text.setColor(Color::Green);
text.setStyle(sf::Text::Bold | sf::Text::Underlined);

std::ostringstream playerScore;
playerScore << p.score;
text.setString("����� ����� ���� ���� �������:" + playerScore.str());//������ ������ ������
text.setPosition(5, 5);//������ ������� ������
window.draw(text);//������ ���� �����

		window.draw(p.sprite);

		for (it = enemies.begin(); it != enemies.end(); it++)
		{
			if ((*it)->life)
			window.draw((*it)->sprite); //������ enemies �������
		}
		
		for (it = Bullets.begin(); it != Bullets.end(); it++)
		{
			
			if ((*it)->life) //���� ���� ����, �� ������ �
				window.draw((*it)->sprite);
			
		}

		window.display();
	}



        
return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//����� �������� ������������ � ���������� �����
void Player::checkCollisionWithMap(float Dx, float Dy)	
	{
	for (int i = y / 47; i < (y + h) / 47; i++)//���������� �� ��������� �����
		for (int j = x / 47; j<(x + w) / 47; j++)
		{
			if ((TileMap[i][j] == '0') || (TileMap[i][j] == '1'))//���� ������� ������ ����� ��� �������
			{
			if (Dy > 0) { y = i * 47 - h;  dy = 0; }//�� Y 
			if (Dy < 0) { y = i * 47 + 47; dy = 0; }//������������ � �������� ������ 
			if (Dx > 0) { x = j * 47 - w;  dx = 0; }//� ������ ����� �����
			if (Dx < 0) { x = j * 47 + 47; dx = 0; }// � ����� ����� �����
			}
			if (TileMap[i][j] == '2')
			{
	               score++;
	               TileMap[i][j] = ' ';
                }
			if (TileMap[i][j] == '3')
			{
				score += 50;
				std::cout << "YOU ARE WINNER!!!";
				TileMap[i][j] = ' ';
			}

			}
				
		}
	



void Enemy::checkCollisionWithMap(double Dx, double Dy)//�-��� �������� ������������ � ������
{
		for (int i = y / 47; i < (y + h) / 47; i++)//���������� �� ��������� �����
			for (int j = x / 47; j<(x + w) / 47; j++)
			{
				if ((TileMap[i][j] == '0') || (TileMap[i][j] == '1'))//���� ������� - ������ �����
				{
					if (Dy > 0) {
						y = i * 47 - h;  dy = -0.1; 
						direction = rand() % (4); //����������� �������� �����
						}//�� Y 
					if (Dy < 0) {
						y = i * 47 + 47; dy = 0.1; 
						direction = rand() % (4);//����������� �������� ����� 
						}//������������ � �������� ������ 
					if (Dx > 0) {
						x = j * 47 - w; dx = -0.1; 
						direction = rand() % (4);//����������� �������� ����� 
						}//� ������ ����� �����
					if (Dx < 0) {
						x = j * 47 + 47; dx = 0.1; 
						direction = rand() % (4); //����������� �������� �����
						}// � ����� ����� �����
				}
			}
	}

  void Bullet::update(float time)
	{
		
		switch (direction)
		{
		case 0: dx = -speed; dy = 0;  break;
		case 1: dx = speed; dy = 0;   break;
		case 2: dx = 0; dy = -speed;  break;
		case 3: dx = 0; dy = speed;   break;
		case 4: dx = 0; dy = 0; break;
		}

		if (life)
		{
			x += dx*time;
			y += dy*time;

		


			for (int i =y / 47; i < (y + h) / 47; i++)
				for (int j = x / 47; j < (x + w) / 47; j++)
				{
					if ((TileMap[i][j] == '0') || (TileMap[i][j] == '1'))
				
					life = false;
					
				}
				sprite.setPosition(x + w / 2, y + h /2);
				
		}
	}