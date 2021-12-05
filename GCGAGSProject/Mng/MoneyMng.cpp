#include <string>
#include <DxLib.h>
#include "MoneyMng.h"
#include "UISubTest.h"
#include "ImageMng.h"
#include "MouseMng.h"
#include "UIMng.h"

MoneyMng* MoneyMng::sInstance = nullptr;

void MoneyMng::Update(void)
{
	Vector2 nowMPos = lpMouseMng.GetMousePos();

	if (lpMouseMng.IsLeftClick())
	{
		if (nowMPos.x >= pos_.x &&
			nowMPos.x <= pos_.x + size_.x &&
			nowMPos.y >= pos_.y &&
			nowMPos.y < pos_.y + size_.y)
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
			pos_ = { nowMPos.x + mouseSubpos_.x,nowMPos.y + mouseSubpos_.y };
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
			/*if (lpMouseMng.IsLeftClick() && !(lpMouseMng.GetOldInputDat() & MOUSE_INPUT_LEFT))
			{
				dropgrabF_ = true;
				grabNum_ = 1;
			}*/

			if (!subUIDispF_)
			{
				if (mousecount_ > 30)
				{
					if (subUi_ == -1)
					{
						subUi_ = lpUIMng.CreateUI(std::make_unique<UISubTest>(nowMPos, Vector2{ 250,50 }));
					}
					lpUIMng.SetUIPos(subUi_, nowMPos);
					lpUIMng.SetUIDate(subUi_, "Ç®ã‡Ç≈Ç∑ÅI");
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

		if (!gf)
		{
			mousecount_ = 0;
			subUIDispF_ = false;
		}
	}

	if (!subUIDispF_)
	{
		lpUIMng.DeleteUI(subUi_);
		subUi_ = -1;
	}
}

void MoneyMng::Draw(void)
{
	SetDrawScreen(screeenH_);
	ClsDrawScreen();
	DrawBox(0, 5, size_.x, size_.y, 0xffffff, true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawBox(0,size_.y / 2 + 20, size_.x, size_.y / 2 + 20 + size_.y / 2, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	//DrawBox(0, 0, size_.x, 15, 0xffffff, true);
	DrawFormatString(5, 15, 0x000000, "%dGold",money_);

	SetDrawScreen(DX_SCREEN_BACK);
	lpImglMng.ScreenAddDrawQue(screeenH_,pos_, 30);

	
}

MoneyMng::MoneyMng()
{
	startF_ = false;
	money_ = 150; 
	std::string str = GetCommandLine();
	size_t pos = str.find(' ');
	auto tmpt = str.substr(pos + 1);

	if (!tmpt.empty())
	{
		money_ = 9999;
	}
	subUi_ = -1;
	pos_ = { 5,500 };
	size_ = { 150,50 };
	grabF_ = false;
	subUIDispF_ = false;
	mousecount_ = 0;
	tmpmoney_ = 0;
	screeenH_ = MakeScreen(size_.x, size_.y + 10, TRUE);
}

MoneyMng::~MoneyMng()
{
}
