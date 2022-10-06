#include "MapDatList.h"
std::vector<mapChipDate> MapDatList::oldmapdatalist_;
int MapDatList::nowPos_ = 0;
int MapDatList::getPos_ = 0;
void MapDatList::AddDate(mapChipDate dat)
{
	oldmapdatalist_.emplace_back(dat);
	SetPos();
}

mapChipDate MapDatList::GetDate(void)
{
	if (oldmapdatalist_.size() == 0)
	{
		return mapChipDate();
	}
	if (getPos_ == -1)
	{
		return mapChipDate();
	}
	int tmpPos = getPos_;
	if (getPos_ - 1 < 0)
	{
		auto tmpdat = oldmapdatalist_[tmpPos];
		Init();
		getPos_ = -1;
		return tmpdat;
	}
	getPos_--;
	return oldmapdatalist_[tmpPos];
}

void MapDatList::Init(void)
{
	nowPos_ = 0;
	getPos_ = -1;
	oldmapdatalist_.clear();
}

void MapDatList::SetPos(void)
{
	getPos_ = nowPos_;
	nowPos_++;
}
