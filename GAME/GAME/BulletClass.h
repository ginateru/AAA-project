#include"Class.h"

/////////////////////////////////////////////////����� ����//////////////////////////////////////////////////////////////////////

class Bullet :public Entity{//����� ����
public:
	int direction;//����������� ����

	Bullet(Image &image, float X, float Y, int W, int H, std::string  Name, int dir);

	void update(float time) ;

	
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////