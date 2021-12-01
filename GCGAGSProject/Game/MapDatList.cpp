#include "MapDatList.h"
std::array<mapChipDate, 20> MapDatList::oldmapdatalist_;
int MapDatList::nowPos_ = 0;
int MapDatList::getPos_ = 0;
void MapDatList::AddDate(mapChipDate dat)
{
	getPos_ = nowPos_;
	oldmapdatalist_[nowPos_] = dat;
	SetPos();
}

mapChipDate MapDatList::GetDate(void)
{
	if (getPos_ == -1)
	{
		return mapChipDate();;
	}
	int tmpPos = getPos_;
	if (getPos_ - 1 < 0 && nowPos_ != oldmapdatalist_.size() - static_cast<size_t>(1))
	{
		getPos_ = static_cast<int>(oldmapdatalist_.size()) - 1;
		return oldmapdatalist_[tmpPos];
	}
	if (getPos_ - 1 == nowPos_)
	{
		auto tmpdat = oldmapdatalist_[tmpPos];
		Init();
		return tmpdat;
	}
	getPos_--;
	return oldmapdatalist_[tmpPos];
}

void MapDatList::Init(void)
{
	nowPos_ = 0;
	getPos_ = -1;
}

void MapDatList::SetPos(void)
{
	nowPos_++;
	if (nowPos_ >= oldmapdatalist_.size())
	{
		nowPos_ = 0;
	}
}
