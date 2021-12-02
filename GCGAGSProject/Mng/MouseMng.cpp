#include <memory>
#include <DxLib.h>
#include "MouseMng.h"
#include "ImageMng.h"
#include "MoneyMng.h"

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
	}
	if (clickCount_ > 10)
	{
		clickCount_ = 0;
	}
	if (clickCount_ >= 1)
	{
		clickCount_++;
	}
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
			DrawRotaGraph(clickPos_.x + 10, clickPos_.y, static_cast<float>(clickCount_) /10, 0, lpImglMng.GetGraphHandle("ring1.png"), true);
		}
		else
		{
			DrawRotaGraph(clickPos_.x+10, clickPos_.y, static_cast<float>(clickCount_) / 10, 0, lpImglMng.GetGraphHandle("ring2.png"), true);
		}
	}
	if (lpMoneyMng.GetStartFlag())
	{
		if (grabF_)
		{
			DrawGraph(mousePos_.x + 10, mousePos_.y-25, lpImglMng.GetGraphHandle("handGrab.png"), true);
		}
		else
		{
			DrawGraph(mousePos_.x + 10, mousePos_.y-15, lpImglMng.GetGraphHandle("handNormal.png"), true);
		}
	}
	else
	{
		DrawGraph(mousePos_.x+10, mousePos_.y, lpImglMng.GetGraphHandle("mouse.png"), true);
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
	isClickRight_ = false;

	mousePos_ = std::move(Vector2{0,0});

	for (auto& pos : oldMousePos_)
	{
		pos = std::move(Vector2{ 0,0 });
	}
	isMoving_ = false;
	isExclusive_ = false;
	mouseSclH_ = -1;
}

MouseMng::~MouseMng()
{
}
