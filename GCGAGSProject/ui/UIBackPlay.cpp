#include <DxLib.h>
#include "UIBackPlay.h"
#include "ImageMng.h"
#include "UISubTest.h"
#include "MoneyMng.h"
#include "MouseMng.h"
#include "UIMng.h"

UIBackPlay::UIBackPlay()
{
	SetDate();
}

UIBackPlay::UIBackPlay(Vector2 pos, Vector2 size) :UIBase(pos, size)
{
	subUIDispF_ = false;
	subUi_ = -1;
	mousecount_ = 0;
	fcon_ = 0;
}

UIBackPlay::~UIBackPlay()
{
}

void UIBackPlay::Update(void)
{
	Vector2 nowMPos = lpMouseMng.GetMousePos();
	if (nowMPos.x >= pos_.x &&
		nowMPos.x <= pos_.x + size_.x &&
		nowMPos.y >= pos_.y &&
		nowMPos.y <= pos_.y + size_.y)
	{
		if (lpMouseMng.IsLeftClick() && !(lpMouseMng.GetOldInputDat() & MOUSE_INPUT_LEFT))
		{
			if (fcon_ > 30 % 2 != 0)
			{
				lpMoneyMng.SetStartFlag(false);
			}
		}
		if (!subUIDispF_)
		{
			if (mousecount_ > 60)
			{
				if (subUi_ == -1)
				{
					subUi_ = lpUIMng.CreateUI(std::make_unique<UISubTest>(nowMPos, Vector2{ 100,50 }));
				}
				lpUIMng.SetUIPos(subUi_, nowMPos);
				lpUIMng.SetUIDate(subUi_, "‚à‚Ç‚é");
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

	fcon_++;
}

void UIBackPlay::SetDate(void)
{
}

void UIBackPlay::Draw(void)
{
	Reset();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawBox(0, 0, size_.x, size_.y, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawBox(0, 0, size_.x, 10, 0xffffff, true);
	DrawFormatString(5, 15, 0xffffff, "‚à‚Ç‚é");
	//DrawGraph(0, 0, lpImglMng.GetGraphHandle("Mine.png").first, false);

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

