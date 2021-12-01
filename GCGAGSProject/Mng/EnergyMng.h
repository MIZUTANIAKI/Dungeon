#pragma once
#include <memory>
#define lpEnergyMng EnergyMng::GetInstance()

class MyEnergy;

class EnergyMng
{
public:
	static EnergyMng& GetInstance(void)
	{
		Create();
		return *sInstance;
	}

	static void Create()
	{
		if (sInstance == nullptr)
		{
			sInstance = new EnergyMng();
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
	bool SubEnergy(int num);

	int GetEnergy();

	void Init(void);

private:
	static EnergyMng* sInstance;
	EnergyMng();
	~EnergyMng();
	int count_;
};

