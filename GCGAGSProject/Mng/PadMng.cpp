#include <DxLib.h>
#include "PadMng.h"
#include "Controller.h"
#include "PadInput.h"
#include "MouseMng.h"

PadMng* PadMng::sInstance = nullptr;

void PadMng::Update(void)
{
	if (!padPlugIn_)
	{
		padPlugIn_ = controller_->Setup();
		return;
	}
	controller_->Update();
	if (GetNowControllerData(InputID::BtnA))
	{
		lpMouseMng.SetMouseClickR();
	}
	if (GetNowControllerData(InputID::BtnB))
	{
		lpMouseMng.SetMouseClickL();
	}
	MovePos();
}

void PadMng::MovePos()
{
	Vector2 tmpMovePos = { 0,0 };
	int moveNum = 5;
	if (GetNowControllerData(InputID::LS))
	{
		moveNum = 1;
	}
	if (GetNowControllerData(InputID::Up))
	{
		tmpMovePos.y-= moveNum;
	}
	if (GetNowControllerData(InputID::Right))
	{
		tmpMovePos.x+= moveNum;
	}
	if (GetNowControllerData(InputID::Down))
	{
		tmpMovePos.y+= moveNum;
	}
	if (GetNowControllerData(InputID::Left))
	{
		tmpMovePos.x-= moveNum;
	}
	if (tmpMovePos == Vector2(0, 0))
	{
		return;
	}
	lpMouseMng.AddPos(tmpMovePos);
}

PadMng::PadMng()
{
	controller_ = std::make_unique<PadInput>();
	padPlugIn_ = controller_->Setup();
}

PadMng::~PadMng()
{
}