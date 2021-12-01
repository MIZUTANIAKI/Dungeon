#pragma once
#include <vector>
#include "MapMng.h"
#include "Explorer.h"
#include "common/Vector2.h"

class SaveMap
{
public:
	SaveMap();
	~SaveMap();

	void StartOutPut();
	void StartInPut(int num);

	mapChipDate GetMapdate()
	{
		return mapdat_;
	}

	void SetMapdate(mapChipDate dat)
	{
		mapdat_ = dat;
	}

private:
	mapChipDate mapdat_;
};

