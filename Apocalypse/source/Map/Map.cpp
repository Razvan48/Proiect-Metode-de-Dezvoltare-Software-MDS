#include "Map.h"

#include <iostream>
#include <sstream>

#include "../Renderer/SpriteRenderer.h"
#include "../ResourceManager/ResourceManager.h"

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
			// TODO:
			//this->staticObjects.back().emplace_back(TexturableEntity((double)this->staticObjects.back().size() - 0.5, (double)this->staticObjects.size() - 0.5, 1.0, 1.0, 0.0, 0.0, code));
			this->staticObjects.back().emplace_back(TexturableEntity((double)this->staticObjects.back().size() * 28.0f, (double)this->staticObjects.size() * 28.0f, 28.0f, 28.0f, 0.0, 0.0, code));
		}
	}

	in.close();
}

TexturableEntity& Map::getCell(int x, int y)
{
	if (x < 0 || x > this->staticObjects[0].size())
	{
		// TODO:
	}
	if (y < 0 || y > this->staticObjects.size())
	{
		// TODO:
	}

	return this->staticObjects[y][x];
}

void Map::draw()
{
	// TODO:
	for (int i = 0; i < 18; ++i)
	{
		for (int j = 0; j < 18; ++j)
		{
			this->staticObjects[i][j].draw();
		}
	}
}

