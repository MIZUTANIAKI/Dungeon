#include <DxLib.h>
#include "RoadTime.h"
#include "WFUtility.h"
#include "ImageMng.h"

RoadTime::RoadTime(int num)
{
	Init(num);
	time_ = 0;
	rsita_ = 0;
}

RoadTime::~RoadTime()
{
}

void RoadTime::Update(float deltaTime)
{
	time_ += deltaTime;
	//rsita_ = time_;
	rsita_ += 60 * deltaTime;
	if (rsita_ > 360)
	{
		rsita_ = 0;
	}
}

void RoadTime::Draw(float deltaTime)
{
	SetDrawScreen(screenH_);
	ClsDrawScreen();

	DrawLine(0, screenSize_.y - screenSize_.y / 5, screenSize_.x, screenSize_.y - screenSize_.y / 5, 0xffffff, 5);

	for (int i = 1; i <= 10; i++)
	{
		float rad = WFUtility::DegToRad(rsita_ + i * (360 / 10));
		Vector2 pos = { static_cast<int>((screenSize_.x - 60) + (45 * cos(rad))),static_cast<int>((screenSize_.y - 75) + (45 * sin(rad))) };

		if (i % 2 == 0)
		{
			DrawRotaGraph(pos.x, pos.y, 0.5, 0, lpImglMng.GetGraphHandle("ring1.png"), true);
			//lpImglMng.GraphAddDrawQue("ring1.png", pos, 2);
		}
		if (i % 2 != 0)
		{
			DrawRotaGraph(pos.x, pos.y, 0.5, 0, lpImglMng.GetGraphHandle("ring2.png"), true);
			//lpImglMng.GraphAddDrawQue("ring2.png", pos, 2);
		}
	}
	DrawString((screenSize_.x - 180), (screenSize_.y - 25), "NowLoading", 0xccffff);
	std::string tmpstr = static_cast<int>(time_) % 3 == 0 ? "." : static_cast<int>(time_) % 3 == 1 ? ".." : "...";

	DrawString((screenSize_.x - 40), (screenSize_.y - 25), tmpstr.c_str(), 0xccffff);
	SetDrawScreen(DX_SCREEN_BACK);
	lpImglMng.ScreenAddDrawQue(screenH_, 0);
}

void RoadTime::Init(int num)
{
	GetDrawScreenSize(&screenSize_.x, &screenSize_.y);
	screenH_ = MakeScreen(screenSize_.x, screenSize_.y, true);
}