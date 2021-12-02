#include <DxLib.h>
#include "Vector2.h"
#include "StartScene.h"
#include "TitleScene.h"
#include "ImageMng.h"
#include "CronoMng.h"
#include "KeyMng.h"
#include "SoundMng.h"

UNBS StartScene::Update(UNBS own)
{
	time_ += lpCronoMng.GetDeltaTime();
	if (static_cast<int>(time_) == 1)
	{
		if (atenNum_ == 2)
		{
			atenNum_++;
		}
	}
	if (static_cast<int>(time_) == 3)
	{
		if (atenNum_ == 0)
		{
			atenNum_++;
		}
		if (atenNum_ >= 4)
		{
			time_ = 0;
			atenNum_++;
		}
	}

	if (static_cast<int>(time_) == 17)
	{
		if (atenNum_ >= 8)
		{
			return std::move(std::make_unique<TitleScene>());
		}
	}
	if (lpKeyMng.CheckKeyTrg(KeyBindID::Ok))
	{
		if (atenNum_ == 3)
		{
			time_ = 0;
			atenNum_++;
			lpSoundMng.SoundPlay("title.mp3");
		}
		if (atenNum_ == 1)
		{
			time_ = 0;
			atenNum_++;
		}
	}
	return std::move(own);
}

StartScene::StartScene()
{
	time_ = 0;
	atenNum_ = 0;
	lpImglMng.LoadGraph("aten0.png");
	lpImglMng.LoadGraph("aten1.png");
	lpImglMng.LoadGraph("title0.png");
	lpImglMng.LoadGraph("title1.png");
	lpImglMng.LoadGraph("title2.png");
	lpImglMng.LoadGraph("title3.png");
	lpImglMng.LoadGraph("titleback.png");
	lpImglMng.LoadGraph("titlef.png");
	lpImglMng.LoadGraph("wood.png");
	lpSoundMng.LoadSound("title.mp3");
	graphPos_[0] = -10;
	graphPos_[1] = -10;
	graphPos_[2] = 10;
	graphPos_[3] = 0;
	graphPos_[3] = -10;
}

StartScene::StartScene(UNBS own)
{
	time_ = 0;
	atenNum_ = 0;
	lpImglMng.LoadGraph("aten0.png");
	lpImglMng.LoadGraph("aten1.png");
	lpImglMng.LoadGraph("title0.png");
	lpImglMng.LoadGraph("title1.png");
	lpImglMng.LoadGraph("title2.png");
	lpImglMng.LoadGraph("title3.png");
	lpImglMng.LoadGraph("titleback.png");
	lpImglMng.LoadGraph("titlef.png");
	lpImglMng.LoadGraph("wood.png");
	lpSoundMng.LoadSound("title.mp3");
	graphPos_[0] = -10;
	graphPos_[1] = -10;
	graphPos_[2] = 10;
	graphPos_[3] = 0;
	graphPos_[4] = -10;
}

StartScene::~StartScene()
{
}

void StartScene::Draw()
{
	if (atenNum_ == 1)
	{
		lpImglMng.GraphAddDrawQue("aten0.png", { 0,0 }, 0);
	}
	if (atenNum_ == 3)
	{
		lpImglMng.GraphAddDrawQue("aten1.png", { 0,0 }, 0);
	}
	if (atenNum_ >= 7)
	{
		lpImglMng.GraphAddDrawQue("wood.png", { 0,static_cast<int>(graphPos_[3]) }, 0);
	}
	if (atenNum_ >= 8)
	{
		lpImglMng.GraphAddDrawQue("title0.png", { 0,static_cast<int>(graphPos_[4]) }, 0);
	}
	if (atenNum_ >= 4)
	{
		lpImglMng.GraphAddDrawQue("title1.png", { 0,static_cast<int>(graphPos_[0]) }, 0);
	}
	if (atenNum_ >= 5)
	{
		lpImglMng.GraphAddDrawQue("title2.png", { 0,static_cast<int>(graphPos_[1]) }, 0);
	}
	if (atenNum_ >= 6)
	{
		lpImglMng.GraphAddDrawQue("title3.png", { 0,static_cast<int>(graphPos_[2]) }, 0);
	}
}
