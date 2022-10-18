#pragma once
#include <vector>
#include <map>
#include "Vector2.h"
#include "MapMng.h"
#include "Explorer.h"

#define lpRHSMng RightHandSearch::GetInstance()

class RightHandSearch
{
public:

	static RightHandSearch& GetInstance(void)
	{

		Create();
		return *sInstance;
	}

	static void Create()
	{
		if (sInstance == nullptr)
		{
			sInstance = new RightHandSearch();
		}
	}

	static void Destroy()
	{
		if (sInstance != nullptr)
		{
			delete sInstance;
		}
		sInstance = nullptr;
	}

	void SetMapDate(mapChipDate dat)
	{
		mapdat_.clear();
		mapdat_ = dat;
	}

	mapChipDate GetMapDate(void)
	{
		return mapdat_;
	}
	BlockDate GetMapDate(Vector2 pos)
	{
		if (pos.x < mapdat_[0].size() && pos.y < mapdat_.size() && pos.x >= 0 && pos.y >= 0)
		{
			if (Check(pos))
			{
				return BlockDate::Road;
			}
			return BlockDate::Block;
		}
		return BlockDate::Road;
	}

	MoveDir CheckMove(Vector2 pos, MoveDir dir);
	MoveDir CheckMoveSweev(Vector2 pos, MoveDir dir);
	MoveDir CheckMoveBlock(Vector2 pos, MoveDir dir);
	MoveDir CheckMoveL(Vector2 pos, MoveDir dir);
	MoveDir CheckMoveRL(Vector2 pos, MoveDir dir);
	
	BlockEdge GetMapChipHit(Vector2 pos);

	bool Check(Vector2 pos);

private:
	static RightHandSearch* sInstance;

	mapChipDate mapdat_;

	int movenum = -1;

	RightHandSearch();
	~RightHandSearch();
};

