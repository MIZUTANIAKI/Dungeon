#include <DxLib.h>
#include "UISubTest.h"
#include "ImageMng.h"

UISubTest::UISubTest()
{
}

UISubTest::UISubTest(Vector2 pos, Vector2 size) :UIBase(pos, size)
{
	drawDate_ = "test";
}

UISubTest::~UISubTest()
{
}

void UISubTest::Update(void)
{
}

void UISubTest::SetDate(void)
{
}

void UISubTest::SetDate(std::string str)
{
	drawDate_ = str;
}

void UISubTest::Draw(void)
{
	Reset();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
	DrawBox(0, 10, size_.x, size_.y, 0xffffff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawBox(0, 0, size_.x, 10, 0xffffff, true);
	DrawFormatString(5, 15, 0x000000, drawDate_.c_str());
	SetDrawScreen(DX_SCREEN_BACK);
	lpImglMng.ScreenAddDrawQue(screenHandle_, pos_, 70);
}
