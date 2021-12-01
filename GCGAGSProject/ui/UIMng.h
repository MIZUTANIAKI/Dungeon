#pragma once
#include "UIBase.h"
#include <map>
#include <string>

#define lpUIMng UIMng::GetInstance()

class UIMng
{
public:
	static UIMng& GetInstance(void)
	{
		Create();
		return *sInstance;
	}

	static void Create()
	{
		if (sInstance == nullptr)
		{
			sInstance = new UIMng();
		}
	}

	static void Destroy()
	{
		if (sInstance != nullptr)
		{
			delete sInstance;
		}
		sInstance = nullptr;
	}

	void Update(void);

	void Draw(void);
	void FastDraw(void);
	int CreateUI(UNUI uidate);
	int CreateUI(UNUI uidate,bool fastDrawF);
	void SetUIPos(int uiID, Vector2 pos)
	{
		for (const auto& ui : uiVec_)
		{
			if (ui.first == uiID)
			{
				ui.second.first->SetPos(pos);
			}
		}
	}
	void SetUIDate(int uiID, std::string dat)
	{
		for (const auto& ui : uiVec_)
		{
			if (ui.first == uiID)
			{
				ui.second.first->SetDate(dat);
			}
		}
	}
	void DeleteAllUI(void)
	{
		auto itr = uiVec_.begin();
		while (itr != uiVec_.end())
		{
			{
				itr = uiVec_.erase(itr);
			}
		}
	}

	void DeleteUI(int uiid)
	{
		auto itr = uiVec_.begin();
		int count = 0;
		while (itr != uiVec_.end())
		{
			if ((*itr).first == uiid)
			{
				itr = uiVec_.erase(itr);
			}
			else
			{
				itr++;
			}
		}
	}
private:
	static UIMng* sInstance;
	std::map<int, std::pair<UNUI, bool>> uiVec_;

	UIMng();
	~UIMng();
};

