#pragma once
#include <vector>
#include <map>
#include <utility>
#include <string>
#include <memory>
#include "Vector2.h"
#include "MapMng.h"
#include "Explorer.h"

class MapSelect
{
public:
	MapSelect();
	~MapSelect();

	void Update(float deltaTime);

	void SetPlaterPos();

	void BuildRoad(Vector2& nowMPos);

	void Draw(float deltaTime);

	bool CheckDraw(int x, int y);

	void Init();

	void SetStageID(int stageID);
	void SaveStage(void);

	//int GetMapNum() const noexcept
	//{
	//	return mapNum_;
	//}

	mapChipDate GetMapdate() const noexcept
	{
		return mapdat_;
	}

	std::vector<std::unique_ptr<Explorer>> GetDateBox(void)noexcept
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

private:
	bool IsDubDate(Vector2 pos);
	void DrawEdge(Vector2 pos);
	BlockEdge isMapEdge(Vector2 pos);

	void ResetMap(void);
	void RoadMapDat(int stageID = 0);
	void SaveMapDat(int num = 0);

	mapChipDate mapdat_;

	Vector2 mapSize_;
	std::map<BlockDate, std::string> blockImg_;

	Vector2 mapPos_;
	std::vector<std::string>roadImg_;

	std::vector<std::unique_ptr<Explorer>> dateBox_;

	int mapNum_;
	int screenH_;
	Vector2 screenSize_;
	bool pressZ_;
	
	int mouseOldPosY_;
};
