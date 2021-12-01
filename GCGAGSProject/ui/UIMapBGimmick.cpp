#include <DxLib.h>
#include "UIMapBGimmick.h"
#include "ImageMng.h"
#include "UISubTest.h"
#include "ReadMng.h"
#include "MapMng.h"
#include "UIGimmickMenu.h"
#include "MouseMng.h"
#include "UIMng.h"

UIMapBGimmick::UIMapBGimmick()
{
	SetDate();
}

UIMapBGimmick::UIMapBGimmick(Vector2 pos, Vector2 size) :UIBase(pos, size)
{
	subUIDispF_ = false;
	subUi_ = -1;
	gimmickUi_ = -1;
	mousecount_ = 0;
	gimmickUiDispF_ = false;
}

UIMapBGimmick::~UIMapBGimmick()
{
}

void UIMapBGimmick::Update(void)
{
	Vector2 nowMPos = lpMouseMng.GetMousePos();

	if (nowMPos.x >= pos_.x &&
		nowMPos.x <= pos_.x + size_.x &&
		nowMPos.y >= pos_.y&&
		nowMPos.y <= pos_.y + size_.y)
	{
		if (lpMouseMng.IsLeftClick() && !(lpMouseMng.GetOldInputDat() & MOUSE_INPUT_LEFT))
		{
			gimmickUiDispF_ = true;
			if (gimmickUi_ == -1)
			{
				gimmickUi_ = lpUIMng.CreateUI(std::make_unique<UIGimmickMenu>(nowMPos, Vector2{ 155,100 }));
			}
			lpUIMng.SetUIPos(gimmickUi_, nowMPos);
			lpMapMng.SetMapMode(MapMode::Gimmick);
		}
		if (!subUIDispF_ && !gimmickUiDispF_)
		{
			if (mousecount_ > 60)
			{
				if (subUi_ == -1)
				{
					subUi_ = lpUIMng.CreateUI(std::make_unique<UISubTest>(nowMPos, Vector2{ 190,50 }));
				}
				lpUIMng.SetUIPos(subUi_, nowMPos);
				lpUIMng.SetUIDate(subUi_, "ギミックを書く？");
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
	if (lpMapMng.GetMapMode() != MapMode::Gimmick)
	{
		if (gimmickUiDispF_)
		{
			gimmickUiDispF_ = false;
		}
	}
	if (lpMouseMng.IsRightClick() && !!(lpMouseMng.GetOldInputDat() & MOUSE_INPUT_RIGHT))
	{
		if (gimmickUiDispF_)
		{
			gimmickUiDispF_ = false;
			lpMapMng.SetMapMode(MapMode::Main);
		}
	}

	if (!subUIDispF_)
	{
		lpUIMng.DeleteUI(subUi_);
		subUi_ = -1;
	}
	if (!gimmickUiDispF_)
	{
		lpUIMng.DeleteUI(gimmickUi_);
		gimmickUi_ = -1;
	}
}

void UIMapBGimmick::SetDate(void)
{
}

void UIMapBGimmick::Draw(void)
{
	Reset();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawBox(0, 0, size_.x, size_.y, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	//DrawBox(0, 0, size_.x, 10, 0xfff0000, true);
	DrawGraph(0, 0, lpImglMng.GetGraphHandle("Trap.png"), false);

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
