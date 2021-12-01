#pragma once
#include "common/Vector2.h"
#include <vector>
#include <map>

#define lpMapMng MapMng::GetInstance()

struct BlockEdge
{
	bool up = false;
	bool right = false;
	bool down = false;
	bool left = false;
};

enum class MapMode
{
	Main,
	Gimmick,
	Monster,
};

enum class MapDropDateID
{
	None,
	Spike,
	Gate,
	Slime,
	Desmodus,
	Rook,
	Max,
};

enum class BlockDate
{
	Block,
	Road,
	Start,
	Goal,
	DRoad,
	Spike,
	Gate,
};

struct ExplorerDateBox
{
	MapDropDateID id;
	Vector2 pos;
};

using mapChipDate = std::vector<std::vector<BlockDate >>;

class MapMng
{
public:
	static MapMng& GetInstance(void)
	{

		Create();
		return *sInstance;
	}

	static void Create()
	{
		if (sInstance == nullptr)
		{
			sInstance = new MapMng();
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

	MapMode GetMapMode()
	{
		return mapMode_;
	}

	void SetMapMode(MapMode mode)
	{
		mapMode_ = mode;
	}

	bool IsDrop(void)
	{
		if (dropF_)
		{
			dropF_ = false;
			return true;
		}
		return false;
	}

	void SetDrop(MapDropDateID id, Vector2 pos)
	{
		dropPos_ = pos;
		dropF_ = true;
		dropID_ = id;
	}

	MapDropDateID GetDropID(void)
	{
		return dropID_;
	}

	Vector2 GetDropPos(void)
	{
		return dropPos_;
	}
	bool GetDropEndF(MapDropDateID id);
	void SetDropEndF(MapDropDateID id,bool flag)
	{
		dropEndF_.at(id) = flag;
	}
private:
	static MapMng* sInstance;
	MapMode mapMode_;
	MapMng();
	~MapMng();
	bool dropF_;
	MapDropDateID dropID_;
	Vector2 dropPos_;
	std::map< MapDropDateID, bool> dropEndF_;
};

