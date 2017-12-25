
#ifndef __MAP_H__
#define __MAP_H__


#include <SFML\Graphics.hpp>
const int HEIGHT_MAP = 13;//размер карты по высоте
const int WIDTH_MAP = 17;//размер карты по ширине 

std::string TileMap[HEIGHT_MAP] = {
	"00000000000000000",
	"0               0",
	"0               0",
	"0               0",
	"0               0",
	"                0", 
	"                0",
	"                0",
	"0               0",
	"0               0",
	"0               0",
	"0               0",
	"00000000000000000",
};
#endif