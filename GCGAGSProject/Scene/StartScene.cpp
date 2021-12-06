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
	if (lpCronoMng.IsOneSecond())
	{
		maskPos1_.x += 1;
		maskPos1_.y += 1;
		maskPos2_.x += 1;
		maskPos2_.y += 1;
		if (maskPos1_.x >= screenSize_.x && maskPos1_.y >= screenSize_.y)
		{
			maskPos1_ = { -3820,-2160 };
		}
		if (maskPos2_.x >= screenSize_.x && maskPos2_.y >= screenSize_.y)
		{
			maskPos2_ = { -3820,-2160 };
		}
	}
	if (static_cast<int>(time_) >= 1)
	{
		if (atenNum_ == 2)
		{
			atenNum_++;
		}
	}
	if (static_cast<int>(time_) >= 3)
	{
		if (atenNum_ == 0)
		{
			atenNum_++;
		}
		if (atenNum_ >= 4&& atenNum_ < 8)
		{
			time_ = 0;
			atenNum_++;
		}
	}
	if (atenNum_ >= 4 && (lpKeyMng.CheckKeyTrg(KeyBindID::Ok) || lpKeyMng.CheckKeyTrg(KeyBindID::No)))
	{
		return std::move(std::make_unique<TitleScene>());
	}
	if (time_ >= 4)
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
	Init();
}

StartScene::StartScene(UNBS own)
{
	Init();
}

void StartScene::Init()
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
	lpImglMng.LoadGraph("ster.png");
	lpImglMng.LoadGraph("wood.png");
	lpImglMng.LoadGraph("space.png");
	lpImglMng.LoadGraph("space2.png");
	lpImglMng.LoadGraph("space3.png");
	lpSoundMng.LoadSound("title.mp3");
	GetDrawScreenSize(&screenSize_.x, &screenSize_.y);
	screenH_ = MakeScreen(screenSize_.x, screenSize_.y, true);
	graphPos_[0] = static_cast<float>(screenSize_.y - 97);
	graphPos_[1] = -100;
	graphPos_[2] = 100;
	graphPos_[3] = 0;
	graphPos_[4] = 0;
	graphAlpha_[0] = 0;
	graphAlpha_[1] = 0;
	graphAlpha_[2] = 0;
	graphAlpha_[3] = 0;
	graphAlpha_[4] = 0;
	maskHandle_ = LoadMask("resource\\img/titlemask.png");
	maskHandle1_ = LoadMask("resource\\img/title2.png");
	maskHandle2_ = LoadMask("resource\\img/title3mask.png");
	maskPos1_ = { -3820,-2160 };
	maskPos2_ = { 0,0 };
}

StartScene::~StartScene()
{
}

void StartScene::Draw()
{
	//lpImglMng.GraphAddDrawQue("space2.png", maskPos1_, 0);
	//lpImglMng.GraphAddDrawQue("space2.bmp", { maskPos1_.x,maskPos1_.y - 2160 }, 0);
	//lpImglMng.GraphAddDrawQue("space2.png", maskPos2_, 0);
	//lpImglMng.GraphAddDrawQue("space2.bmp", { maskPos2_.x,maskPos2_.y - 2160 }, 0);
	if (atenNum_ == 1)
	{
		lpImglMng.GraphAddDrawQue("aten0.png", { 0,0 }, 0);
	}
	if (atenNum_ == 3)
	{
		lpImglMng.GraphAddDrawQue("aten1.png", { 0,0 }, 0);
	}
	SetDrawScreen(screenH_);
	ClsDrawScreen();
	if (atenNum_ >= 4)
	{
		if (graphAlpha_[3] < 255)
		{
			graphAlpha_[3] += 255 / 5;
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, graphAlpha_[3]);
		lpImglMng.DrawImg("wood.png", { 0,static_cast<int>(graphPos_[3]) });
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, graphAlpha_[3]);
		if (graphAlpha_[4] < 255)
		{
			graphAlpha_[4] += 5;
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, graphAlpha_[4]);
		lpImglMng.DrawImg("title0.png", { 0,static_cast<int>(graphPos_[4]) });
		if (atenNum_ >= 7)
		{
			if (graphPos_[1] < 0)
			{
				graphPos_[1]++;
			}
			if (graphAlpha_[1] < 255)
			{
				graphAlpha_[1] += 5;
			}
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, graphAlpha_[1]);
			lpImglMng.DrawImg("title2.png", { 0,static_cast<int>(graphPos_[1]) });
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, graphAlpha_[1]);

			if (graphPos_[1] > -50)
			{
				if (graphPos_[2] > 0)
				{
					graphPos_[2]--;
				}
				if (graphAlpha_[2] < 255)
				{
					graphAlpha_[2] += 5;
				}
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, graphAlpha_[2]);
				lpImglMng.DrawImg("title3.png", { 0,static_cast<int>(graphPos_[2]) });
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, graphAlpha_[2]);


			}

			//CreateMaskScreen();
			//DrawMask(0, static_cast<int>(graphPos_[1]), maskHandle1_, DX_MASKTRANS_WHITE);
			//lpImglMng.DrawImg("space3.png", { 0,0 });
			//lpImglMng.DrawImg("space2.png", maskPos1_);
			//lpImglMng.DrawImg("space2.png", maskPos2_);
			//DeleteMaskScreen();
			//CreateMaskScreen();
			//DrawMask(0, static_cast<int>(graphPos_[2]) + 100, maskHandle2_, DX_MASKTRANS_WHITE);
			//lpImglMng.DrawImg("space3.png", { 0,0 });
			//lpImglMng.DrawImg("space2.png", maskPos1_);
			//lpImglMng.DrawImg("space2.png", maskPos2_);
			//DeleteMaskScreen();
		}
		if (atenNum_ >= 8)
		{
			CreateMaskScreen();
			DrawMask(0, 0, maskHandle_, DX_MASKTRANS_BLACK);
			lpImglMng.DrawImg("space3.png", { 0,0 });
			lpImglMng.DrawImg("space2.png", maskPos1_);
			lpImglMng.DrawImg("space2.png", maskPos2_);
			DeleteMaskScreen();
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, graphAlpha_[4]);
		if (graphPos_[0] > 0 && lpCronoMng.IsOneSecond())
		{
			graphPos_[0]--;
		}
		if (graphAlpha_[0] < 255)
		{
			graphAlpha_[0] ++;
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, graphAlpha_[0]);
		lpImglMng.DrawImg("title1.png", { 0,static_cast<int>(graphPos_[0]) });
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, graphAlpha_[0]);
	}
	if (atenNum_ >= 5)
	{
		//if (graphAlpha_[4] < 255)
		//{
		//	graphAlpha_[4] += 10;
		//}
		//SetDrawBlendMode(DX_BLENDMODE_ALPHA, graphAlpha_[4]);
		//lpImglMng.DrawImg("title0.png", { 0,static_cast<int>(graphPos_[4]) });
		//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, graphAlpha_[4]);
	}
	if (atenNum_ >= 6)
	{
	}

	SetDrawScreen(DX_SCREEN_BACK);
	lpImglMng.ScreenAddDrawQue(screenH_);
}
