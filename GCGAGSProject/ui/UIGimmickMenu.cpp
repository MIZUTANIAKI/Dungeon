#include <DxLib.h>
#include "UIGimmickMenu.h"
#include "ImageMng.h"
#include "UISubTest.h"
#include "ReadMng.h"
#include "MapMng.h"
#include "MouseMng.h"
#include "UIMng.h"

UIGimmickMenu::UIGimmickMenu()
{
	SetDate();
}

UIGimmickMenu::UIGimmickMenu(Vector2 pos, Vector2 size) :UIBase(pos, size)
{
	grabF_ = false;
	subUIDispF_ = false;
	dropgrabF_ = false;
	subUi_ = -1;
	mousecount_ = 0;
	grabNum_ = 0;
}

UIGimmickMenu::~UIGimmickMenu()
{
}

void UIGimmickMenu::Update(void)
{
	Vector2 nowMPos = lpMouseMng.GetMousePos();
	if (lpMouseMng.IsLeftClick())
	{
		if (nowMPos.x >= pos_.x &&
			nowMPos.x <= pos_.x + size_.x &&
			nowMPos.y >= pos_.y &&
			nowMPos.y < pos_.y + 15)
		{
			if (!grabF_)
			{
				lpMouseMng.SetExclusive(true);
				grabF_ = true;
				mouseSubpos_.x = pos_.x - nowMPos.x;
				mouseSubpos_.y = pos_.y - nowMPos.y;
			}
		}
		if (grabF_)
		{
			SetPos({ nowMPos.x + mouseSubpos_.x,nowMPos.y + mouseSubpos_.y });
		}
	}
	else
	{
		lpMouseMng.SetExclusive(false);
		grabF_ = false;
	}

	{
		bool gf = false;
		if (nowMPos.x >= pos_.x &&
			nowMPos.x <= pos_.x + size_.x &&
			nowMPos.y >= pos_.y + 15 &&
			nowMPos.y <= pos_.y + size_.y/2)
		{
			gf = true;
			if (lpMouseMng.IsLeftClick() && !(lpMouseMng.GetOldInputDat() & MOUSE_INPUT_LEFT))
			{
				dropgrabF_ = true;
				grabNum_ = 1;
			}
			
			if (!subUIDispF_)
			{
				if (mousecount_ > 60)
				{
					if (subUi_ == -1)
					{
						subUi_ = lpUIMng.CreateUI(std::make_unique<UISubTest>(nowMPos, Vector2{ 200,50 }));
					}
					lpUIMng.SetUIPos(subUi_, nowMPos);
					lpUIMng.SetUIDate(subUi_, "ヒトにダメージ！");
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

		if (nowMPos.x >= pos_.x &&
			nowMPos.x <= pos_.x + size_.x &&
			nowMPos.y >= pos_.y + size_.y / 2 + 20 &&
			nowMPos.y <= pos_.y + size_.y / 2 + 20 + size_.y / 2)
		{
			gf = true;
			if (lpMouseMng.IsLeftClick() && !(lpMouseMng.GetOldInputDat() & MOUSE_INPUT_LEFT))
			{
				dropgrabF_ = true;
				grabNum_ = 2;
			}

			if (!subUIDispF_)
			{
				if (mousecount_ > 60)
				{
					if (subUi_ == -1)
					{
						subUi_ = lpUIMng.CreateUI(std::make_unique<UISubTest>(nowMPos, Vector2{ 200,50 }));
					}
					lpUIMng.SetUIPos(subUi_, nowMPos);
					lpUIMng.SetUIDate(subUi_, "ヒトを止める");
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
		
		if(!gf)
		{
			mousecount_ = 0;
			subUIDispF_ = false;
		}
	}
	if (dropgrabF_)
	{
		if (!lpMouseMng.IsLeftClick())
		{
			if (grabNum_ == 1)
			{
				lpMapMng.SetDrop(MapDropDateID::Spike, nowMPos);
			}
			else if (grabNum_ == 2)
			{
				lpMapMng.SetDrop(MapDropDateID::Gate, nowMPos);
			}
			grabNum_ = 0;
			dropgrabF_ = false;
		}
		grabF_ = false;
	}

	if (!subUIDispF_)
	{
		lpUIMng.DeleteUI(subUi_);
		subUi_ = -1;
	}
}

void UIGimmickMenu::SetDate(void)
{
}

void UIGimmickMenu::Draw(void)
{
	Reset();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawBox(0, 10, size_.x, size_.y/2, 0x000000, true);
	DrawBox(0, size_.y / 2+20, size_.x, size_.y / 2+20 + size_.y / 2, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	//DrawBox(0, 0, size_.x, 15, 0xffffff, true);
	DrawFormatString(5, 15, 0x000000, "スパイク");
	DrawFormatString(5, size_.y / 2 + 20 + 5, 0x000000, "シールド");

	if (dropgrabF_)
	{
		if (grabNum_ == 1)
		{
			lpImglMng.GraphAddDrawQue("drop.png", { lpMouseMng.GetMousePos().x - 32 / 2, lpMouseMng.GetMousePos().y - 32 / 2 }, 51);
		}
		else if (grabNum_ == 2)
		{
			lpImglMng.GraphAddDrawQue("gate.png", { lpMouseMng.GetMousePos().x - 32 / 2, lpMouseMng.GetMousePos().y - 32 / 2 }, 51);
		}
	}

	SetDrawScreen(DX_SCREEN_BACK);
	lpImglMng.GraphAddDrawQue("Clip.png", pos_, 40);
	lpImglMng.ScreenAddDrawQue(screenHandle_, pos_, 50);
}
