#pragma once

#include <fstream>
#include <vector>
#include <string>

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
	int WIDTH;	// TODO: init
	int HEIGHT;	// TODO: init

	std::vector<std::vector<int>> map;

public:
	static Map& get();
	inline int getWidth() { return WIDTH; };
	inline int getHeight() { return HEIGHT; };
	int getCell(int x, int y);
	void readMap(const std::string& path);
};

