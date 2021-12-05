#pragma once
#include "UIBase.h"
#include "common/Vector2.h"

#define lpMoneyMng MoneyMng::GetInstance()

class MoneyMng
{
public:
	static MoneyMng& GetInstance(void)
	{
		Create();
		return *sInstance;
	}

	static void Create()
	{
		if (sInstance == nullptr)
		{
			sInstance = new MoneyMng();
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

	void SetStartFlag(bool flag) {
		startF_ = flag;
	}

	bool GetStartFlag(void) {
		return startF_;
	}

	int GetMoney(void)
	{
		return money_;
	}

	bool SubMoney(int num)
	{
		if (money_ - num < 0)
		{
			return false;
		}

		money_ -= num;
		return true;
	}

	int AddMoney(int num)
	{
		return money_ += num;
	}

	int AddTmpMoney(int num)
	{
		return tmpmoney_ += num;
	}

	int GettmpMoney(void)
	{
		int rtnMoney = tmpmoney_;
		tmpmoney_ = 0;
		return rtnMoney;
	}

	void SetMoney(int num)
	{
		money_ = num;
	}
private:
	static MoneyMng* sInstance;

	MoneyMng();
	~MoneyMng();

	bool startF_;

	int money_;
	int tmpmoney_;

	Vector2 mouseSubpos_;

	int subUi_;
	bool subUIDispF_;
	bool grabF_;
	int mousecount_;
	Vector2 pos_;
	Vector2 size_;
	int screeenH_;
};

