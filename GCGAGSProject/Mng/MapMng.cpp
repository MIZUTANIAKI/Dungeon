#include "MapMng.h"

MapMng* MapMng::sInstance = nullptr;

bool MapMng::GetDropEndF(MapDropDateID id)
{
	bool rtnF = dropEndF_.at(id);
	if (rtnF)
	{
		dropEndF_.at(id) = false;
	}
	return rtnF;
}

MapMng::MapMng()
{
	mapMode_ = MapMode::Main;
	dropF_ = false;
	dropID_ = MapDropDateID::Slime;
	for (MapDropDateID id = MapDropDateID::None; id != MapDropDateID::Max; id = static_cast<MapDropDateID>(static_cast<int>(id) + 1))
	{
		dropEndF_.try_emplace(id, false);
	}
}

MapMng::~MapMng()
{
}


