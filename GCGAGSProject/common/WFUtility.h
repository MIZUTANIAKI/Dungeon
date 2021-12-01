#pragma once
#include <memory>
#include "Vector2.h"

class WFUtility
{
public:
	static float DegToRad(float deg);

	static double DegToRad(double deg);

	static float RadToDeg(float deg);

	static double RadToDeg(double deg);

	static Vector2 VecFltToVecInt(Vector2flt vec);

	static Vector2 VecDblToVecInt(Vector2dbl vec);

	static Vector2flt VecIntToVecFlt(Vector2 vec);

	static Vector2flt VecDblToVecFlt(Vector2dbl vec);

	static Vector2dbl VecIntToVecDbl(Vector2 vec);

	static Vector2dbl VecFltToVecDbl(Vector2flt vec);
private:
};