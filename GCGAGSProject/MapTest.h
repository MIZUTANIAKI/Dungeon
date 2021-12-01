#pragma once
#include <vector>
#include <map>
#include <utility>
#include <string>
#include <memory>
#include "Vector2.h"
#include "MapMng.h"
#include "Explorer.h"

class MapTest
{
public:
	MapTest();
	~MapTest();

	void Update();

	void Draw();

	mapChipDate GetMapdate()
	{
		return mapdat_;
	}
	std::vector<std::unique_ptr<Explorer>> GetDateBox(void)
	{
		return  std::move(dateBox_);
	}

	void SetDateBox(std::vector<std::unique_ptr<Explorer>> dat)
	{
		dateBox_ = std::move(dat);
		for (auto& dat : dateBox_)
		{
			dat->SetMapMos(mapPos_);
			dat->DefPos();
		}
	}

	void Init();

private:
	bool IsDubDate(Vector2 pos);
	void DrawEdge(Vector2 pos);
	BlockEdge isMapEdge(Vector2 pos);

	void ResetMap(void);
	void RoadMapDat(void);
	void SaveMapDat(void);

	mapChipDate mapdat_;

	Vector2 mapSize_;
	std::map<BlockDate, std::string> blockImg_;

	int screenH_;
	Vector2 mapPos_;
	std::vector<std::string>roadImg_;

	std::vector<std::unique_ptr<Explorer>> dateBox_;
	//std::vector<SetDateBox> dateBox_;
};

