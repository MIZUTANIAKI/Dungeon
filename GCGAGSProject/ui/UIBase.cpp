#include <DxLib.h>
#include "UIBase.h"

UIBase::UIBase()
{
	pos_ = { 0, 0 };
	size_ = { 50, 50 };
}

UIBase::UIBase(Vector2 pos, Vector2 size)
{
	CreatSscreen(pos, size);
}

void UIBase::Reset(void)
{
	SetDrawScreen(screenHandle_);
	ClsDrawScreen();
}

void UIBase::SetPos(Vector2 pos)
{
	pos_ = pos;
}

void UIBase::CreatSscreen(Vector2 pos, Vector2 size)
{
	pos_ = pos;
	size_ = size;
	screenHandle_ = MakeScreen(size_.x, size_.y + 10, TRUE);
}
