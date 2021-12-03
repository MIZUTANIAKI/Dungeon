#include "EnergyMng.h"
#include "CronoMng.h"
#include "MyEnergy.h"

EnergyMng* EnergyMng::sInstance = nullptr;

void EnergyMng::Update(void)
{
	if (lpCronoMng.IsOneSecond())
	{
		count_++;
	}
	if (count_ > 10)
	{
		MyEnergy::SetEnergy(MyEnergy::GetEnergy() + 1);
		count_ = 0;
	}
}

bool EnergyMng::SubEnergy(int num)
{
	if (MyEnergy::GetEnergy() - num < 0)
	{
		return false;
	}
	MyEnergy::SetEnergy(MyEnergy::GetEnergy() - num);
	return true;
}

int EnergyMng::GetEnergy()
{
	return MyEnergy::GetEnergy();
}

void EnergyMng::Init(void)
{
	MyEnergy::SetEnergy(10);
	count_ = 0;
}

EnergyMng::EnergyMng()
{
	count_ = 0;
}

EnergyMng::~EnergyMng()
{
}
