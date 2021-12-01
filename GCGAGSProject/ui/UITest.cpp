#include <DxLib.h>
#include "UITest.h"
#include "ImageMng.h"
#include "UISubTest.h"
#include "ReadMng.h"
#include "MouseMng.h"

UITest::UITest()
{
	SetDate();
}

UITest::UITest(Vector2 pos, Vector2 size) :UIBase(pos, size)
{
	grabF_ = false;
	subUIDispF_ = false;
	subUi_ = std::make_unique<UISubTest>(pos, Vector2{ 250,50 });
	mousecount_ = 0;
}

UITest::~UITest()
{
}

void UITest::Update(void)
{
	Vector2 nowMPos = lpMouseMng.GetMousePos();
	if (lpMouseMng.IsLeftClick())
	{
		if (nowMPos.x >= pos_.x &&
			nowMPos.x <= pos_.x + size_.x &&
			nowMPos.y >= pos_.y &&
			nowMPos.y < pos_.y + 10)
		{
			if (!grabF_)
			{
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
		grabF_ = false;
	}

	{

		if (nowMPos.x >= pos_.x &&
			nowMPos.x <= pos_.x + size_.x &&
			nowMPos.y >= pos_.y + 10 &&
			nowMPos.y <= pos_.y + size_.y)
		{
			if (!subUIDispF_)
			{
				if (mousecount_ > 60)
				{
					subUi_->SetPos(nowMPos);
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
	}

	if (subUIDispF_)
	{
		subUi_->Update();
	}
}

void UITest::SetDate(void)
{
	//std::map<std::string, std::vector<std::string>> tmpfilemap = lpReadMng.GetDate("testUI.txt").dataMap;
	//mousepos_ = { 0,0 };
	//mouseInputDate_ = 0;
	//subUIDispF_ = false;
	//subUIDispF_ = false;
	//if (tmpfilemap.find("Pos") != tmpfilemap.end())
	//{
	//	pos_.x = atoi(tmpfilemap.find("Pos")->second[0].c_str());
	//	pos_.y = atoi(tmpfilemap.find("Pos")->second[1].c_str());
	//}
	//else
	//{
	//	pos_ = { 0,0 };
	//}
	//if (tmpfilemap.find("Size") != tmpfilemap.end())
	//{
	//	size_.x = atoi(tmpfilemap.find("Size")->second[0].c_str());
	//	size_.y = atoi(tmpfilemap.find("Size")->second[1].c_str());
	//}
	//else
	//{
	//	size_ = { 0,0 };
	//}
	//for (const auto& tfile : tmpfilemap)
	//{
	//	if (tfile.first.c_str() == "Btn")
	//	{
	//		uiDateVector_.emplace_back(UiDateType::Btn, tfile.second[0]);
	//	}
	//	if (tfile.first.c_str() == "Txt")
	//	{
	//		uiDateVector_.emplace_back(UiDateType::Txt, tfile.second[0]);
	//	}
	//}
}

void UITest::Draw(void)
{
	subUi_->Reset();
	Reset();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawBox(0, 10, size_.x, size_.y, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawBox(0, 0, size_.x, 10, 0xffffff, true);
	DrawFormatString(5, 15, 0xffffff, "‚¢‚ë‚Í‚É‚Ù‚¦‚Æ‚¿‚è‚Ê‚é‚ð");

	//int uiDateLineCount = 0;
	//for (const auto& uidate : uiDateVector_)
	//{
	//	if (uidate.first == UiDateType::Btn)
	//	{

	//	}
	//	if (uidate.first == UiDateType::Txt)
	//	{

	//	}
	//	uiDateLineCount++;
	//}
	SetDrawScreen(DX_SCREEN_BACK);
	DrawGraph(pos_.x, pos_.y, screenHandle_, true);
	if (subUIDispF_)
	{
		subUi_->Draw();
	}
}
