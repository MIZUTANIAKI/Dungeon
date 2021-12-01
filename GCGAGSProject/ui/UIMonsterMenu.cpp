#include <DxLib.h>
#include "UIMonsterMenu.h"
#include "ImageMng.h"
#include "UISubTest.h"
#include "ReadMng.h"
#include "MapMng.h"
#include "MouseMng.h"
#include "UIMng.h"

UIMonsterMenu::UIMonsterMenu()
{
	SetDate();
}

UIMonsterMenu::UIMonsterMenu(Vector2 pos, Vector2 size)
{
	grabF_ = false;
	subUIDispF_ = false;
	dropgrabF_ = false;
	subUi_ = -1;
	mousecount_ = 0;
	grabNum_ = 0;

	pos_ = pos;
	size_ = size;
	screenHandle_ = MakeScreen(size_.x, size_.y *2, TRUE);
}

UIMonsterMenu::~UIMonsterMenu()
{
}

void UIMonsterMenu::Update(void)
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
			nowMPos.y <= pos_.y + size_.y / 2)
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
						subUi_ = lpUIMng.CreateUI(std::make_unique<UISubTest>(nowMPos, Vector2{ 250,50 }));
					}
					lpUIMng.SetUIPos(subUi_, nowMPos);
					lpUIMng.SetUIDate(subUi_, "äpÇã»Ç™ÇÁÇ»Ç≠Çƒé„Ç¢");
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
						subUi_ = lpUIMng.CreateUI(std::make_unique<UISubTest>(nowMPos, Vector2{ 250,50 }));
					}
					lpUIMng.SetUIPos(subUi_, nowMPos);
					lpUIMng.SetUIDate(subUi_, "úpújÇµÇ†Ç‹ÇËã≠Ç≠Ç»Ç¢");
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
				lpMapMng.SetDrop(MapDropDateID::Slime, nowMPos);
			}
			else if (grabNum_ == 2)
			{
				lpMapMng.SetDrop(MapDropDateID::Desmodus, nowMPos);
			}

			dropgrabF_ = false;
			grabNum_ = 0;
		}
		grabF_ = false;
	}

	if (!subUIDispF_)
	{
		lpUIMng.DeleteUI(subUi_);
		subUi_ = -1;
	}
}

void UIMonsterMenu::SetDate(void)
{
}

void UIMonsterMenu::Draw(void)
{
	Reset();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawBox(0, 10, size_.x, size_.y / 2, 0x000000, true);
	DrawBox(0, size_.y / 2 + 20, size_.x, size_.y / 2 + 20 + size_.y / 2, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	//DrawBox(0, 0, size_.x, 15, 0xffffff, true);
	DrawFormatString(5, 15, 0x000000, "ÉÇÉìÉXÉ^Å[1");
	DrawFormatString(5, size_.y / 2 + 20 + 5, 0x000000, "ÉÇÉìÉXÉ^Å[2");
	if (dropgrabF_)
	{
		if (grabNum_ == 1)
		{
			lpImglMng.GraphAddDrawQue("testC2.png", { lpMouseMng.GetMousePos().x - 32 / 2, lpMouseMng.GetMousePos().y - 32 / 2 - 32 }, 51);
		}
		else if (grabNum_ == 2)
		{
			lpImglMng.GraphAddDrawQue("testC3.png", { lpMouseMng.GetMousePos().x - 32 / 2, lpMouseMng.GetMousePos().y - 32 / 2 - 32 }, 51);
		}
	}

	SetDrawScreen(DX_SCREEN_BACK);

	lpImglMng.GraphAddDrawQue("Clip.png", pos_, 40);
	lpImglMng.ScreenAddDrawQue(screenHandle_, pos_, 50);

}
