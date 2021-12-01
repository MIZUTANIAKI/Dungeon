#include <DxLib.h>
#include "UIPlayPopEne2.h"
#include "ImageMng.h"
#include "UISubTest.h"
#include "ReadMng.h"
#include "MapMng.h"
#include "MouseMng.h"
#include "UIMng.h"

UIPlayPopEne2::UIPlayPopEne2()
{
	SetDate();
}

UIPlayPopEne2::UIPlayPopEne2(Vector2 pos, Vector2 size) :UIBase(pos, size)
{
	subUIDispF_ = false;
	subUi_ = -1;
	mousecount_ = 0;
}

UIPlayPopEne2::~UIPlayPopEne2()
{
}

void UIPlayPopEne2::Update(void)
{
	Vector2 nowMPos = lpMouseMng.GetMousePos();
	if (nowMPos.x >= pos_.x &&
		nowMPos.x <= pos_.x + size_.x &&
		nowMPos.y >= pos_.y &&
		nowMPos.y <= pos_.y + size_.y)
	{
		if (lpMouseMng.IsLeftClick() && !(lpMouseMng.GetOldInputDat() & MOUSE_INPUT_LEFT))
		{
			lpMapMng.SetDrop(MapDropDateID::Desmodus, nowMPos);
		}
		if (!subUIDispF_)
		{
			if (mousecount_ > 60)
			{
				if (subUi_ == -1)
				{
					subUi_ = lpUIMng.CreateUI(std::make_unique<UISubTest>(nowMPos, Vector2{ 150,50 }));
				}
				lpUIMng.SetUIPos(subUi_, nowMPos);
				lpUIMng.SetUIDate(subUi_, "ñ°ï˚è¢ä´2");
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

	if (!subUIDispF_)
	{
		lpUIMng.DeleteUI(subUi_);
		subUi_ = -1;
	}
}

void UIPlayPopEne2::SetDate(void)
{
}

void UIPlayPopEne2::Draw(void)
{
	Reset();
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawBox(0, 0, size_.x, size_.y, 0xffffff, true);
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	//DrawBox(0, 0, size_.x, 10, 0xffffff, true);
	//DrawGraph(0, 0, lpImglMng.GetGraphHandle("Mine.png").first, false);
	DrawGraph(size_.x / 2 - 32 / 2, size_.y / 2 - 32, lpImglMng.GetGraphHandle("testC3.png"), true);

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


