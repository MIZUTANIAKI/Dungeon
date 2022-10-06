#pragma once
#include <vector>
#include "MapMng.h"

class MapDatList
{
public:
	static void AddDate(mapChipDate dat);
	static mapChipDate GetDate(void);
	static void Init(void);
private:
	static void SetPos(void);
	static std::vector<mapChipDate> oldmapdatalist_;
	static int nowPos_;
	static int getPos_;
};

