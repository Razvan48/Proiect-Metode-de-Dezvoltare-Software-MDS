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
		this->map.emplace_back();

		std::string line;
		std::getline(in, line);
		std::stringstream ss(line);

		std::string code;
		while (ss >> code)
		{
			if (code[0] == 'M')
			{
				this->map.back().emplace_back(std::make_shared<Wall>((double)this->map.back().size() - 0.5, (double)this->map.size() - 0.5, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, code));
			}
			else if (code[0] == '.')
			{
				this->map.back().emplace_back(std::make_shared<Floor>((double)this->map.back().size() - 0.5, (double)this->map.size() - 0.5, 1.0, 1.0, 0.0, 0.0, code));
			}
			else if (code[0] == 'D')
			{

			}
		}
	}

	in.close();
}

void Map::draw()
{
	for (int i = 0; i < this->map.size(); ++i)
	{
		for (int j = 0; j < this->map[0].size(); ++j)
		{
			this->map[i][j]->draw();
		}
	}
}

