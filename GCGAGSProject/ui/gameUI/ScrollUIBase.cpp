#include <DxLib.h>
#include "ScrollUIBase.h"
#include "MouseMng.h"
#include "EnergyMng.h"
#include "ImageMng.h"
#include "SoundMng.h"

bool ScrollUIBase::isLock_ = false;

ScrollUIBase::ScrollUIBase()
{
	pos_ = { 0,0 };
	id_ = MapDropDateID::None;
	cost_ = 0;
	isClick_ = false;
}

ScrollUIBase::ScrollUIBase(Vector2 pos)
{
	pos_ = { 0,0 };
	id_ = MapDropDateID::None;
	cost_ = 0;
	isClick_ = false;
}

void ScrollUIBase::SetLockOff(void)
{
	isLock_ = false;
}

void ScrollUIBase::DragMove(void)
{
	if (!isClick_ && !isLock_)
	{
		if (lpMouseMng.IsLeftClick())
		{
			if (lpMouseMng.GetMousePos().x > pos_.x &&
				lpMouseMng.GetMousePos().x < pos_.x + 60 &&
				lpMouseMng.GetMousePos().y > pos_.y &&
				lpMouseMng.GetMousePos().y < pos_.y + 60
				)
			{
				isClick_ = true;
				isLock_ = true;
				clickPos_ = lpMouseMng.GetMousePos();
				lpMouseMng.SetGrab(true);
				lpSoundMng.SoundPlay("grab.mp3");
			}
		}
	}
	if (!lpMouseMng.IsLeftClick())
	{
		if (isClick_&& isLock_)
		{
			lpMouseMng.SetGrab(false);
			if (lpMouseMng.GetMousePos().y < pos_.y)
			{
				if (lpEnergyMng.GetEnergy() >= cost_)
				{
					lpMapMng.SetDrop(id_, lpMouseMng.GetMousePos());
				}
			}
			isClick_ = false;
			isLock_ = false;
		}
	}
}

void ScrollUIBase::DeleteUi()
{
	if (lpMapMng.GetDropEndF(id_) == true)
	{
		delF_ = true;
		lpMouseMng.SetGrab(false);
	}
}

void ScrollUIBase::GrabDraw(void)
{
	if (!isClick_)
	{
		return;
	}
	Vector2 pos = lpMouseMng.GetMousePos();
	if (id_ == MapDropDateID::Slime)
	{
		pos.y -= 50;
		lpImglMng.GraphAddDrawQue("testC2.png", pos, 50);
		return;
	}
	if (id_ == MapDropDateID::Desmodus)
	{
		pos.y -= 50;
		lpImglMng.GraphAddDrawQue("testC3.png", pos, 50);
		return;
	}
	if (id_ == MapDropDateID::Rook)
	{
		pos.y -= 50;
		lpImglMng.GraphAddDrawQue("testC4.png", pos, 50);
		return;
	}
	if (id_ == MapDropDateID::Spike)
	{
		pos.y -= 30;
		lpImglMng.GraphAddDrawQue("drop.png", pos, 50);
		return;
	}
	if (id_ == MapDropDateID::Gate)
	{
		pos.y -= 30;
		lpImglMng.GraphAddDrawQue("gate.png", pos, 50);
		return;
	}
}



