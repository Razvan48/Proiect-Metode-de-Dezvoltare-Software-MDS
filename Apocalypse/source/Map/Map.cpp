#include "Map.h"

Map& Map::get()
{
	static Map instance;

	return instance;
}

int Map::getCell(int x, int y)
{
	if (x < 0 || x >= this->WIDTH || y < 0 || y >= this->HEIGHT)
		return 0;

	return this->map[x][y];
}

void Map::readMap(const std::string& path)
{
	std::ios_base::sync_with_stdio(false);

	std::ifstream in(path);
	in.tie(nullptr);

	in >> this->WIDTH >> this->HEIGHT;

	this->map.resize(this->WIDTH);
	for (int i = 0; i < this->map.size(); ++i)
		this->map[i].resize(this->HEIGHT);

	for (int y = this->HEIGHT - 1; y >= 0; --y)
		for (int x = 0; x < this->WIDTH; ++x)
			in >> this->map[x][y];

	in.close();
}

