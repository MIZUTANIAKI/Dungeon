#pragma once
class MyEnergy
{
public:
	static void SetEnergy(int num);
	static int GetEnergy(void)
	{
		return energy_;
	}

private:
	static int energy_;
};

