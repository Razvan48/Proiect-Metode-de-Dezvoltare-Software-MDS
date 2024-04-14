#include "Map.h"

#include <iostream>
#include <sstream>

#include "../Renderer/SpriteRenderer.h"
#include "../ResourceManager/ResourceManager.h"

#include "../Entity/Door/Door.h"
#include "../Entity/Floor/Floor.h"
#include "../Entity/Wall/Wall.h"

Map& Map::get()
{
	static Map instance;

	return instance;
}

void Map::readMap(const std::string& path)
{
	std::ios_base::sync_with_stdio(false);

	std::ifstream in(path);
	if (in.fail())
	{
		throw std::runtime_error("Cannot open file: " + path);
	}
	in.tie(nullptr);

	while (!in.eof())
	{
		this->staticObjects.emplace_back();

		std::string line;
		std::getline(in, line);
		std::stringstream ss(line);

		std::string code;
		while (ss >> code)
		{
			// TODO: de sters linia 2 (comentata)
			/*
			if (code[0] == 'M')
				this->staticObjects.back().emplace_back(Wall((double)this->staticObjects.back().size() - 0.5, (double)this->staticObjects.size() - 0.5, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, code));
			else if (code[0] == '.')
				this->staticObjects.back().emplace_back(Floor((double)this->staticObjects.back().size() - 0.5, (double)this->staticObjects.size() - 0.5, 1.0, 1.0, 0.0, 0.0, code));
			*/
			this->staticObjects.back().emplace_back(TexturableEntity((double)this->staticObjects.back().size() - 0.5, (double)this->staticObjects.size() - 0.5, 1.0, 1.0, 0.0, 0.0, code));
		}

		/*
		for (int i = 0; i < this->staticObjects.size(); ++i)
		{
			for (int j = 0; j < this->staticObjects[i].size(); ++j)
			{
				this->staticObjects[i][j].setY((double)this->staticObjects.size() - this->staticObjects[i][j].getY());
			}
		}
		*/
	}

	in.close();
}

TexturableEntity& Map::getCell(int x, int y)
{
	if (x < 0 || x > this->staticObjects[0].size())
	{
		// TODO: exceptii
	}
	if (y < 0 || y > this->staticObjects.size())
	{
		// TODO: exceptii
	}

	return this->staticObjects[y][x];
}

void Map::draw()
{
	for (int i = 0; i < this->staticObjects.size(); ++i)
	{
		for (int j = 0; j < this->staticObjects[0].size(); ++j)
		{
			this->staticObjects[i][j].draw();
		}
	}
}

