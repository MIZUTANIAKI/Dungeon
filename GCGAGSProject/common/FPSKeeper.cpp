#include <math.h>
#include <DxLib.h>
#include "FPSKeeper.h"

FPSKeeper::FPSKeeper() :
	setFps_(60)
{
	Init();
}

FPSKeeper::~FPSKeeper()
{
}

bool FPSKeeper::Update(void)
{
	if (timeCount == 0)
	{
		firstTime_ = GetNowCount();
	}
	if (timeCount == setFps_)
	{
		int t = GetNowCount();
		nowFps_ = 1000.f / ((t - firstTime_) / static_cast<float>(setFps_));
		timeCount = 0;
		firstTime_ = t;
	}
	timeCount++;
	return true;
}

void FPSKeeper::Draw()
{
	DrawFormatString(0, 0, 0xff000, "%0.1f", nowFps_);
}

void FPSKeeper::Wait(void)
{
	int tookTime = GetNowCount() - firstTime_;	//‚©‚©‚Á‚½ŽžŠÔ
	int waitTime = timeCount * 1000 / setFps_ - tookTime;	//‘Ò‚Â‚×‚«ŽžŠÔ
	if (waitTime > 0) 
	{
		Sleep(waitTime);	//‘Ò‹@
	}
}

void FPSKeeper::Init(void)
{
	firstTime_ = 0;
	timeCount = 0;
	nowFps_ = 0;
}
