#include <memory>
#include <DxLib.h>
#include "MouseMng.h"
#include "ImageMng.h"
#include "MoneyMng.h"
#include "CronoMng.h"
#include "WFUtility.h"

MouseMng* MouseMng::sInstance = nullptr;

void MouseMng::Update(void)
{
	inputdateold_ = inputdate_;
	int tmpX, tmpY;
	GetMousePoint(&tmpX, &tmpY);
	if (!oldMousePos_.empty())
	{
		if (oldMousePos_.front().x != tmpX || oldMousePos_.front().y != tmpY)
		{
			SetOldPos(mousePos_);
			mousePos_.x = tmpX;
			mousePos_.y = tmpY;
			isMoving_ = true;
		}
		else
		{
			if (oldMousePos_.front() == mousePos_)
			{
				isMoving_ = false;
			}
		}
	}
	inputdate_ = GetMouseInput();
	if (inputdate_ & MOUSE_INPUT_LEFT&& !(inputdateold_ & MOUSE_INPUT_LEFT))
	{
		clickPos_ = mousePos_;
		clickCount_ = 1;
		isClickRight_ = false;
	}
	if (inputdate_ & MOUSE_INPUT_RIGHT&&!(inputdateold_ & MOUSE_INPUT_RIGHT))
	{
		clickPos_ = mousePos_;
		clickCount_ = 1;
		isClickRight_ = true;
		if (lpMoneyMng.GetStartFlag())
		{
			grabAngl_++;
			if (grabAngl_ > 3)
			{
				grabAngl_ = 0;
			}
		}
	}
	if (clickCount_ > 10)
	{
		clickCount_ = 0;
	}
	if (clickCount_ >= 1)
	{
		clickCount_++;
	}
	count_ += lpCronoMng.GetDeltaTime();
}

void MouseMng::Draw(void)
{
	if (mouseSclH_ == -1)
	{
		int scSx, scSy;
		GetDrawScreenSize(&scSx, &scSy);
		mouseSclH_ = MakeScreen(scSx, scSy, true);
	}

	SetDrawScreen(mouseSclH_);
	ClsDrawScreen();

	if (clickCount_ >= 1)
	{
		//DrawCircle(clickPos_.x, clickPos_.y, clickCount_, 0xffffff, true);
		if (!isClickRight_)
		{
			DrawRotaGraph(clickPos_.x, clickPos_.y, static_cast<float>(clickCount_) /10, 0, lpImglMng.GetGraphHandle("ring1.png"), true);
		}
		else
		{
			DrawRotaGraph(clickPos_.x, clickPos_.y, static_cast<float>(clickCount_) / 10, 0, lpImglMng.GetGraphHandle("ring2.png"), true);
		}
	}
	if (notGameF_)
	{
		grabAngl_ = 0;
		grabF_ = false;
		if (static_cast<int>(count_ * 10) / 3 % 3 == 0)
		{
			DrawRotaGraph(mousePos_.x + 32 / 2, mousePos_.y + 32 / 2, 1.0, 0, lpImglMng.GetGraphHandle("CheckMouse1.png"), true, true, true);
		}
		if (static_cast<int>(count_ * 10) / 3 % 3 == 1)
		{
			DrawRotaGraph(mousePos_.x + 32 / 2, mousePos_.y + 32 / 2, 1.0, 0, lpImglMng.GetGraphHandle("CheckMouse2.png"), true, true, true);
		}
		if (static_cast<int>(count_ * 10) / 3 % 3 == 2)
		{
			DrawRotaGraph(mousePos_.x + 32 / 2, mousePos_.y + 32 / 2, 1.0, 0, lpImglMng.GetGraphHandle("CheckMouse3.png"), true, true, true);
		}
	}
	else
	{
		if (lpMoneyMng.GetStartFlag())
		{
			if (grabF_)
			{
				DrawGraph(mousePos_.x, mousePos_.y - 25, lpImglMng.GetGraphHandle("handGrab.png"), true);
				DrawRotaGraph(mousePos_.x + 25 / 2, mousePos_.y - 32-25/2 , 1.0f, grabAngl_ == 0 ? WFUtility::DegToRad(0.0f) : grabAngl_ == 1 ? WFUtility::DegToRad(90.0f) : grabAngl_ == 2 ? WFUtility::DegToRad(180.0f) : WFUtility::DegToRad(270.0f), lpImglMng.GetGraphHandle("arrow.png"), true);
			}
			else
			{
				DrawGraph(mousePos_.x, mousePos_.y - 15, lpImglMng.GetGraphHandle("handNormal.png"), true);
			}
		}
		else
		{
			grabAngl_ = 0;
			grabF_ = false;
			DrawGraph(mousePos_.x, mousePos_.y, lpImglMng.GetGraphHandle("mouse.png"), true);
		}
	}

	SetDrawScreen(DX_SCREEN_BACK);
	lpImglMng.ScreenAddDrawQue(mouseSclH_, 60);
}

bool MouseMng::IsLeftClick(void)
{
	return inputdate_ & MOUSE_INPUT_LEFT;
}

bool MouseMng::IsRightClick(void)
{
	return inputdate_ & MOUSE_INPUT_RIGHT;
}

void MouseMng::SetPos(Vector2 pos)
{
	mousePos_ = pos;
	DxLib::SetMousePoint(mousePos_.x, mousePos_.y);
}

void MouseMng::SetMouseClickR(void)
{
	inputdate_ = MOUSE_INPUT_RIGHT;
}

void MouseMng::SetMouseClickL(void)
{
	inputdate_ = MOUSE_INPUT_LEFT;
}

void MouseMng::SetGrab(bool flag)
{
	grabF_ = flag;
}

void MouseMng::SetNowGame(bool nowtrg)
{
	notGameF_ = nowtrg;
}

void MouseMng::SetOldPos(Vector2 pos)
{
	Vector2 tmpPos=pos;
	for (auto& mp : oldMousePos_)
	{
		Vector2 tmpMp = mp;
		mp = tmpPos;
		tmpPos = std::move(tmpMp);
	}
}

MouseMng::MouseMng()
{
	clickPos_ = std::move(Vector2{0,0});
	clickCount_ = 0;
	count_ = 0;
	isClickRight_ = false;

	mousePos_ = std::move(Vector2{0,0});

	for (auto& pos : oldMousePos_)
	{
		pos = std::move(Vector2{ 0,0 });
	}
	isMoving_ = false;
	isExclusive_ = false;
	mouseSclH_ = -1;
	grabF_ = false;
	notGameF_ = true;
	grabAngl_ = 0;
	grabF_ = false;
}

MouseMng::~MouseMng()
{
}
