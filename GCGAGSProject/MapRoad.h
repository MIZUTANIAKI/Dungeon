#pragma once
#include <map>
#include <string>
#include "common/Vector2.h"
#include "MapMng.h"

class MapRoad
{
public:
	MapRoad();
	~MapRoad();

	mapChipDate GetMapdate()
	{
		return mapdat_;
	}

	void Init();



private:
	void ResetMap(void);
	void RoadMapDat(void);
	void SaveMapDat(void);

	mapChipDate mapdat_;
	Vector2 mapSize_;
	std::map<BlockDate, std::string> blockImg_;
};

