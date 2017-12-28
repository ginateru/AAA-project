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
	float xr = 150 + rand() % 500; //случайна€ координата врага на поле игры по оси УxФ
	float yr = 150 + rand() % 350; //случайна€ координата врага на поле игры по оси УyФ
		//создаем врагов и помещаем в список
		enemies.push_back(new Enemy(enemyImage, xr, yr, 47, 52, "Enemy"));
		enemiesCount += 1; //увеличили счЄтчик врагов
	}


	Image map_image;//объект изображени€ дл€ карты
	map_image.loadFromFile("images/map.png");//загружаем файл дл€ карты
	Texture map;//текстура карты
	map.loadFromImage(map_image);//зар€жаем текстуру картинкой
	Sprite s_map;//создаЄм спрайт дл€ карты
	s_map.setTexture(map);//заливаем текстуру спрайтом

	Clock clock; 
Clock gameTimeClock;//переменна€ игрового времени, будем здесь хранить врем€ игры 
Clock AtackTime; 
Clock PewPew; 
int gameTime = 0;//объ€вили игровое врем€, инициализировали. 

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
while (window.isOpen()) 
{ 
float time = clock.getElapsedTime().asMicroseconds(); 
float AtTime = AtackTime.getElapsedTime().asSeconds(); 
float Pew = PewPew.getElapsedTime().asSeconds(); 
clock.restart(); //перезагружает врем€ 
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
//добавл€ем в список Bullets пулю 
Bullets.push_back(new Bullet(BulletImage, p.x, p.y, 20, 20, "Bullet", p.state)); 
} 
} 
} 
}


								////////////////////////////////////////////////////////////////////////
	

		p.update(time);
		
		for (it = enemies.begin(); it != enemies.end(); it++)
		{
			(*it)->update(time); //запускаем метод update()
		}


		for (it = Bullets.begin(); it != Bullets.end(); it++)
		{
			
			
			(*it)->update(time); //запускаем метод update()
			
		}
		if (p.life == true){//если игрок жив
		for (it = enemies.begin(); it != enemies.end(); it++){//бежим по списку врагов
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


		for (it = Bullets.begin(); it != Bullets.end(); )//говорим что проходимс€ от начала до конца
		{// если этот объект мертв, то удал€ем его
			if ((*it)-> life == false)	{ 
				Entity *b = *it;
				it = Bullets.erase(it);
				delete (b);
			}			
else  
	it++; //и идем курсором (итератором) к след объекту.
		}




		window.clear();

		for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			if (TileMap[i][j] == ' ') s_map.setTextureRect(IntRect(0, 0, 47, 47)); //если встретили символ пробел, то рисуем 1й квадратик
			if (TileMap[i][j] == '0') s_map.setTextureRect(IntRect (47, 0, 47, 47));//если встретили символ 0, то рисуем 2й квадратик
			if (TileMap[i][j] == '1') s_map.setTextureRect(IntRect (94, 0, 47, 47));
			if (TileMap[i][j] == '2') s_map.setTextureRect(IntRect (141, 0, 47, 47));
			if (TileMap[i][j] == '3') s_map.setTextureRect(IntRect (188, 0, 47, 47));
 
 
			s_map.setPosition(j * 47, i * 47);//по сути раскидывает квадратики, превраща€ в карту. то есть задает каждому из них позицию. если убрать, то вс€ карта нарисуетс€ в одном квадрате 32*32 и мы увидим один квадрат
 
			window.draw(s_map);//рисуем квадратики на экран
		}
			Font font;//шрифт 
font.loadFromFile("HANZI.ttf");
Text text("", font, 20);
text.setColor(Color::Green);
text.setStyle(sf::Text::Bold | sf::Text::Underlined);

std::ostringstream playerScore;
playerScore << p.score;
text.setString("—чет:" + playerScore.str());//задает строку тексту
text.setPosition(5, 5);//задаем позицию текста
window.draw(text);//–исуем этот текст

std::ostringstream playerhealth;
playerhealth << p.health;
text.setString("«доровье:" + playerhealth.str());//задает строку тексту
text.setPosition(5, 25);//задаем позицию текста
window.draw(text);//–исуем этот текст

if (p.NoWin == false){
	Text text("", font,60);
text.setColor(Color::Red);
text.setString("ѕќЅ≈ƒј");//задает строку тексту
text.setPosition(250, 250);//задаем позицию текста
window.draw(text);//–исуем этот текст
}
if (p.life == false){
	Text text("", font,60);
text.setColor(Color::Red);
text.setString("ѕќ–ј∆≈Ќ»≈");//задает строку тексту
text.setPosition(200, 250);//задаем позицию текста
window.draw(text);//–исуем этот текст
}
		window.draw(p.sprite);

		for (it = enemies.begin(); it != enemies.end(); it++)
		{
			if ((*it)->life)
			window.draw((*it)->sprite); //рисуем enemies объекты
		}
		
		for (it = Bullets.begin(); it != Bullets.end(); it++)
		{
			
			if ((*it)->life) //если пул€ жива, то рисуем еЄ
				window.draw((*it)->sprite);
			
		}

		window.display();
	}



        
return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ћетод проверки столкновений с элементами карты

	




  