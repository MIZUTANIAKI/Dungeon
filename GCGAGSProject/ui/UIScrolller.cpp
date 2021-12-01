#include <DxLib.h>
#include "MapMng.h"
#include "UIScrolller.h"
//#include "UIMapBGimmick.h"
//#include "UIMapBMonster.h"
#include "gameUI/Monster1.h"
#include "gameUI/Monster2.h"
#include "gameUI/Monster3.h"
#include "gameUI/Gimmick1.h"
#include "gameUI/Gimmick2.h"
#include "ImageMng.h"
#include "EnergyMng.h"
#include "CronoMng.h"

UIScrolller::UIScrolller()
{
	lpImglMng.LoadGraph("backMenyu.png");
	lpImglMng.LoadGraph("menu1.png");
	lpImglMng.LoadGraph("menu2.png");
	lpImglMng.LoadGraph("menu3.png");
	lpImglMng.LoadGraph("menu4.png");
	lpImglMng.LoadGraph("menu5.png");
	GetDrawScreenSize(&defPosX_, &screenSizeY_);
	defPosX_ = defPosX_ / 2 - 60 * 2;
	scrollX_ = defPosX_;
	screenH_ = MakeScreen(defPosX_ + 60 * 4, screenSizeY_, true);
	Init();
}

UIScrolller::~UIScrolller()
{
	lpImglMng.DeleteGraph("backMenyu.png");
	lpImglMng.DeleteGraph("menu1.png");
	lpImglMng.DeleteGraph("menu2.png");
	lpImglMng.DeleteGraph("menu3.png");
	lpImglMng.DeleteGraph("menu4.png");
	lpImglMng.DeleteGraph("menu5.png");
}

void UIScrolller::Update(void)
{
	SpawnUI();
	auto itr = UIVector_.begin();
	while (itr != UIVector_.end())
	{
		if ((*itr)->GetDelFlag() == true || uiF_[(*itr)->GetID()].first == false)
		{
			scrollX_ -= 65;
			uiF_[(*itr)->GetID()].first = false;
			uiF_[(*itr)->GetID()].second = 0;
			itr = UIVector_.erase(itr);
		}
		else
		{
			(*itr)->Update();
			itr++;
		}
	}
	for (auto& uif : uiF_)
	{
		if (!uif.second.first)
		{
			if (lpCronoMng.IsOneSecond())
			{
				if (uif.second.second <= 60 * 20)
				{
					uif.second.second++;
				}
			}
		}
	}
}

void UIScrolller::SpawnUI()
{
	if (lpEnergyMng.GetEnergy() >= 10)
	{
		if (uiF_[MapDropDateID::Slime].first == false)
		{
			//if (uiF_[MapDropDateID::Slime].second < 60 * 5)
			//{
			//	return;
			//}
			uiF_[MapDropDateID::Slime].second = 0;
			UIVector_.emplace_back(std::make_unique<Monster1>(Vector2{ defPosX_ + 60 * 5,screenSizeY_ - 65 }));
			scrollX_ += 65;
			uiF_[MapDropDateID::Slime].first = true;
		}
	}
	else
	{
		if (uiF_[MapDropDateID::Slime].first == true)
		{
			uiF_[MapDropDateID::Slime].first = false;
		}
	}
	if (lpEnergyMng.GetEnergy() >= 30)
	{
		if (uiF_[MapDropDateID::Desmodus].first == false)
		{
			//if (uiF_[MapDropDateID::Desmodus].second < 60*10)
			//{
			//	return;
			//}
			uiF_[MapDropDateID::Desmodus].second = 0;
			UIVector_.emplace_back(std::make_unique<Monster2>(Vector2{ defPosX_ + 60 * 5,screenSizeY_ - 65 }));
			scrollX_ += 65;
			uiF_[MapDropDateID::Desmodus].first = true;
		}
	}
	else
	{
		if (uiF_[MapDropDateID::Desmodus].first == true)
		{
			uiF_[MapDropDateID::Desmodus].first = false;
		}
	}
	if (lpEnergyMng.GetEnergy() >= 40)
	{
		if (uiF_[MapDropDateID::Rook].first == false)
		{
			//if (uiF_[MapDropDateID::Slime].second < 60 * 5)
			//{
			//	return;
			//}
			uiF_[MapDropDateID::Rook].second = 0;
			UIVector_.emplace_back(std::make_unique<Monster3>(Vector2{ defPosX_ + 60 * 5,screenSizeY_ - 65 }));
			scrollX_ += 65;
			uiF_[MapDropDateID::Rook].first = true;
		}
	}
	else
	{
		if (uiF_[MapDropDateID::Rook].first == true)
		{
			uiF_[MapDropDateID::Rook].first = false;
		}
	}
	if (lpEnergyMng.GetEnergy() >= 50)
	{
		if (uiF_[MapDropDateID::Spike].first == false)
		{
			//if (uiF_[MapDropDateID::Spike].second < 60*15)
			//{
			//	return;
			//}
			uiF_[MapDropDateID::Spike].second = 0;
			UIVector_.emplace_back(std::make_unique<Gimmick1>(Vector2{ defPosX_ + 60 * 5,screenSizeY_ - 65 }));
			scrollX_ += 65;
			uiF_[MapDropDateID::Spike].first = true;
		}
	}
	else
	{
		if (uiF_[MapDropDateID::Spike].first == true)
		{
			uiF_[MapDropDateID::Spike].first = false;
		}
	}
	if (lpEnergyMng.GetEnergy() >= 60)
	{
		if (uiF_[MapDropDateID::Gate].first == false)
		{
			//if (uiF_[MapDropDateID::Gate].second < 60*20)
			//{
			//	return;
			//}
			uiF_[MapDropDateID::Gate].second = 0;
			UIVector_.emplace_back(std::make_unique<Gimmick2>(Vector2{ defPosX_ + 60 * 5,screenSizeY_ - 65 }));
			scrollX_ += 65;
			uiF_[MapDropDateID::Gate].first = true;
		}
	}
	else
	{
		if (uiF_[MapDropDateID::Gate].first == true)
		{
			uiF_[MapDropDateID::Gate].first = false;
		}
	}
}

void UIScrolller::Draw(void)
{
	lpImglMng.GraphAddDrawQue("backMenyu.png", { defPosX_ - 5, screenSizeY_ - 70 }, 30);
	SetDrawScreen(screenH_);
	ClsDrawScreen();

	int posx = defPosX_;
	bool initF = false;
	for (auto& ui : UIVector_)
	{
		if (ui->GetPos().x > posx)
		{
			ui->SetPos({ ui->GetPos().x - 1,screenSizeY_ - 65 });
		}
		posx += 65;
		initF = true;
		ui->Draw();
	}
	DrawBox(defPosX_, screenSizeY_ - 80, defPosX_ + 60 * 4, screenSizeY_ - 70, 0x00000, true);
	DrawBox(defPosX_ + 2, screenSizeY_ - 78, defPosX_ + (60 * 4 - 2) * lpEnergyMng.GetEnergy()/ 100 , screenSizeY_ - 72, 0xffffff, true);
	SetDrawScreen(DX_SCREEN_BACK);
	lpImglMng.ScreenAddDrawQue(screenH_, { 0, 0}, 31);
}

void UIScrolller::Init(void)
{
	UIVector_.clear();
	uiF_.clear();
	for (MapDropDateID id = MapDropDateID::None; id != MapDropDateID::Max; id = static_cast<MapDropDateID>(static_cast<int>(id) + 1))
	{
		uiF_.try_emplace(id, std::pair<bool, int>(false, 60 * 20));
	}
}

