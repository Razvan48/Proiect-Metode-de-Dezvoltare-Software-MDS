#pragma once

#include <fstream>
#include <vector>
#include <string>

#include "../Entity/Wall/Wall.h"
#include "../Entity/TexturableEntity.h"
#include "../Entity/AnimatedEntity.h"
#include "../Entity/Door/Door.h"

/*
* Codificare:
* 
* M0 M1 M2 M3 ... M9 MA MB MC ... = coduri de perete
* .0 .1 .2 .3 ... .9 .a .b .c ... = coduri de podea
* D0 D1 D2 D3 ... D9 DA DB DC ... = coduri de usi
*/

class Map
{
private:
	Map() = default;
	~Map() = default;
	Map(const Map& other) = delete;
	Map& operator= (const Map& other) = delete;
	Map(const Map&& other) = delete;
	Map& operator= (const Map&& other) = delete;

private:

	std::vector<std::vector<TexturableEntity>> staticObjects;
	std::vector<Door> doors;

public:
	static Map& get();
	TexturableEntity& getCell(int x, int y);
	void readMap(const std::string& path);
	std::vector<std::vector<TexturableEntity>>& getStaticObjects() { return this->staticObjects; }
	std::vector<Door>& getDoors() { return this->doors; }
	void draw();
};

