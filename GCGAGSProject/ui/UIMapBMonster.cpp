#include <DxLib.h>
#include "UIMapBMonster.h"
#include "ImageMng.h"
#include "UISubTest.h"
#include "ReadMng.h"
#include "MapMng.h"
#include "UIMonsterMenu.h"
#include "MouseMng.h"
#include "UIMng.h"

UIMapBMonster::UIMapBMonster()
{
	SetDate();
}

UIMapBMonster::UIMapBMonster(Vector2 pos, Vector2 size) :UIBase(pos, size)
{
	subUIDispF_ = false;
	subUi_ = -1;
	monsterUi_ = -1;
	mousecount_ = 0;
	monsterUiDispF_ = false;
}

UIMapBMonster::~UIMapBMonster()
{
}

void UIMapBMonster::Update(void)
{
	Vector2 nowMPos = lpMouseMng.GetMousePos();

	if (nowMPos.x >= pos_.x &&
		nowMPos.x <= pos_.x + size_.x &&
		nowMPos.y >= pos_.y &&
		nowMPos.y <= pos_.y + size_.y)
	{
		if (lpMouseMng.IsLeftClick() && !(lpMouseMng.GetOldInputDat() & MOUSE_INPUT_LEFT))
		{
			monsterUiDispF_ = true;

			if (monsterUi_ == -1)
			{
				monsterUi_ = lpUIMng.CreateUI(std::make_unique<UIMonsterMenu>(nowMPos, Vector2{ 155,100 }));
			}
			lpUIMng.SetUIPos(monsterUi_, nowMPos);

			lpMapMng.SetMapMode(MapMode::Monster);
		}
		if (!subUIDispF_ && !monsterUiDispF_)
		{
			if (mousecount_ > 60)
			{
				if (subUi_ == -1)
				{
					subUi_ = lpUIMng.CreateUI(std::make_unique<UISubTest>(nowMPos, Vector2{ 150,50 }));
				}
				lpUIMng.SetUIPos(subUi_, nowMPos);
				lpUIMng.SetUIDate(subUi_, "ÉRÉ}ÇèëÇ≠ÅH");

				subUIDispF_ = true;
			}
		}
		if (lpMouseMng.GetMouseOldPos() == nowMPos)
		{
			mousecount_++;
		}
		else
		{
			mousecount_ = 0;
			subUIDispF_ = false;
		}
	}
	else
	{
		mousecount_ = 0;
		subUIDispF_ = false;
	}
	if (lpMapMng.GetMapMode() != MapMode::Monster)
	{
		if (monsterUiDispF_)
		{
			monsterUiDispF_ = false;
		}
	}
	if (lpMouseMng.IsRightClick() && !!(lpMouseMng.GetOldInputDat() & MOUSE_INPUT_RIGHT))
	{
		if (monsterUiDispF_)
		{
			monsterUiDispF_ = false;
			lpMapMng.SetMapMode(MapMode::Main);
		}
	}


	if (!subUIDispF_)
	{
		lpUIMng.DeleteUI(subUi_);
		subUi_ = -1;
	}
	if (!monsterUiDispF_)
	{
		lpUIMng.DeleteUI(monsterUi_);
		monsterUi_ = -1;
	}
}

void UIMapBMonster::SetDate(void)
{
}

void UIMapBMonster::Draw(void)
{
	Reset();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawBox(0, 0, size_.x, size_.y, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	//DrawBox(0, 0, size_.x, 10, 0xfff0000, true);
	DrawGraph(0, 0, lpImglMng.GetGraphHandle("Monster.png"), false);
	//int uiDateLineCount = 0;
	//for (const auto& uidate : uiDateVector_)
	//{
	//	if (uidate.first == UiDateType::Btn)
	//	{

	//	}
	//	if (uidate.first == UiDateType::Txt)
	//	{

	//	}3
	//	uiDateLineCount++;
	//}
	SetDrawScreen(DX_SCREEN_BACK);
	lpImglMng.ScreenAddDrawQue(screenHandle_, pos_, 30);
}
