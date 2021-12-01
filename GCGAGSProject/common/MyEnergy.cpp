#include "MyEnergy.h"

int MyEnergy::energy_ = 0;

void MyEnergy::SetEnergy(int num)
{
	energy_ = num;
	if (energy_ > 100)
	{
		energy_ = 100;
	}
}
