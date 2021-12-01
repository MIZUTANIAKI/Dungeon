#include <algorithm>
#include <vector>
#include <utility>
#include <memory>
#include <DxLib.h>
#include "MapRoad.h"
#include "SaveMap.h"

MapRoad::MapRoad()
{
	Init();
	RoadMapDat();
}

MapRoad::~MapRoad()
{
}

void MapRoad::Init()
{
	Vector2 tpos = { 15,25 };
	Vector2 tsize = { 100,100 };

	//mapSize_.x = 35;
	//mapSize_.y = 17;
	//mapdat_.resize(mapSize_.y);
	//for (int y = 0; y < mapSize_.y; y++)
	//{
	//	mapdat_[y].resize(mapSize_.x);
	//}

	//for (int y = 0; y < mapSize_.y; y++)
	//{
	//	for (int x = 0; x < mapSize_.x; x++)
	//	{
	//		if (y == 0 && x == mapSize_.x / 2-1)
	//		{
	//			mapdat_[y][x] = BlockDate::Start;
	//		}
	//		else if (y == mapSize_.y - 1 && x == mapSize_.x / 2-1)
	//		{
	//			mapdat_[y][x] = BlockDate::Goal;
	//		}
	//		else
	//		{
	//			mapdat_[y][x] = BlockDate::Block;
	//		}
	//	}
	//}
}

void MapRoad::ResetMap(void)
{
	for (int y = 0; y < mapSize_.y; y++)
	{
		for (int x = 0; x < mapSize_.x; x++)
		{
			if (mapdat_[y][x] != BlockDate::Block && mapdat_[y][x] != BlockDate::Goal && mapdat_[y][x] != BlockDate::Start)
			{
				mapdat_[y][x] = BlockDate::Block;
			}
		}
	}
}

void MapRoad::RoadMapDat(void)
{
	ResetMap();
	//std::unique_ptr<Tmx> tile = std::make_unique<Tmx>("resource//date/map/test.tmx");
	//std::unique_ptr<Tsx> map = std::make_unique<Tsx>("resource//date/map/map.tsx");

	////mapD_.resize(tile->GetlayerNum());
	////////tile->GetMapData(mapdat_);

	//mapSize_ = tile->GetMapSize();
	////cips_ = map->GetCipSize();

	//std::unique_ptr<SaveMap> smap = std::make_unique<SaveMap>();
	//smap->StartInPut(1);
	//mapdat_ = smap->GetMapdate();
}

void MapRoad::SaveMapDat(void)
{
	std::unique_ptr<SaveMap> smap = std::make_unique<SaveMap>();
	smap->SetMapdate(mapdat_);
	smap->StartOutPut();
}
