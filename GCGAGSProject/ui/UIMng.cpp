#include "UIMng.h"

UIMng* UIMng::sInstance = nullptr;

void UIMng::Update(void)
{
	for (const auto& ui : uiVec_)
	{
		ui.second.first->Update();
	}
}

void UIMng::Draw(void)
{
	for (const auto& ui : uiVec_)
	{
		if (!ui.second.second)
		{
			ui.second.first->Draw();
		}
	}
}

void UIMng::FastDraw(void)
{
	for (const auto& ui : uiVec_)
	{
		if (ui.second.second)
		{
			ui.second.first->Draw();
		}
	}
}

int UIMng::CreateUI(UNUI uidate)
{
	bool rtnF = true;
	int num = 0;
	do
	{
		rtnF = true;
		num = rand();
		for (const auto& ui : uiVec_)
		{
			if (num == ui.first)
			{
				rtnF = false;
			}
		}
	} while (!rtnF);
	uiVec_.try_emplace(num, std::pair<UNUI, bool>(std::move<>(uidate), false));
	return num;
}

int UIMng::CreateUI(UNUI uidate, bool fastDrawF)
{
	bool rtnF = true;
	int num = 0;
	do
	{
		rtnF = true;
		num = rand();
		for (const auto& ui : uiVec_)
		{
			if (num == ui.first)
			{
				rtnF = false;
			}
		}
	} while (!rtnF);
	uiVec_.try_emplace(num, std::pair<UNUI, bool>(std::move<>(uidate), fastDrawF));
	return num;
}

UIMng::UIMng()
{
}

UIMng::~UIMng()
{
}
