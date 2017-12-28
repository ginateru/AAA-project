#include <SFML/Graphics.hpp>
#include <iostream> 
#include "Class.h"
#include "BulletClass.h"
#include "EnemyClass.h"
#include "PClass.h"
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

	
	const int ENEMY_COUNT = 7;
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
Clock AtackTime; 
Clock PewPew; 
int gameTime = 0;//�������� ������� �����, ����������������. 

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
while (window.isOpen()) 
{ 
float time = clock.getElapsedTime().asMicroseconds(); 
float AtTime = AtackTime.getElapsedTime().asSeconds(); 
float Pew = PewPew.getElapsedTime().asSeconds(); 
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
if(Pew>0.5 && p.life){ 
PewPew.restart(); 
//��������� � ������ Bullets ���� 
Bullets.push_back(new Bullet(BulletImage, p.x, p.y, 20, 20, "Bullet", p.state)); 
} 
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
					if (AtTime > 2){
						AtackTime.restart();
						p.health--;
					}
				}
			}
		}
		for (no = Bullets.begin(); no != Bullets.end(); no++)
		{
			for (it = enemies.begin(); it != enemies.end();)
			{
				if((*it)->getRect().intersects((*no)->getRect()))
				{
					Entity *b = *it;
					(*it)-> life = false;	
					it = enemies.erase(it);
					delete (b);
					p.score += 5;
				}
				else it++;
			}
		}


		for (it = Bullets.begin(); it != Bullets.end(); )//������� ��� ���������� �� ������ �� �����
		{// ���� ���� ������ �����, �� ������� ���
			if ((*it)-> life == false)	{ 
				Entity *b = *it;
				it = Bullets.erase(it);
				delete (b);
			}			
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
text.setString("����:" + playerScore.str());//������ ������ ������
text.setPosition(5, 5);//������ ������� ������
window.draw(text);//������ ���� �����

std::ostringstream playerhealth;
playerhealth << p.health;
text.setString("��������:" + playerhealth.str());//������ ������ ������
text.setPosition(5, 25);//������ ������� ������
window.draw(text);//������ ���� �����

if (p.NoWin == false){
	Text text("", font,60);
text.setColor(Color::Red);
text.setString("������");//������ ������ ������
text.setPosition(250, 250);//������ ������� ������
window.draw(text);//������ ���� �����
}
if (p.life == false){
	Text text("", font,60);
text.setColor(Color::Red);
text.setString("���������");//������ ������ ������
text.setPosition(200, 250);//������ ������� ������
window.draw(text);//������ ���� �����
}
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

	




  