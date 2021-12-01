#include <DxLib.h>
#include "WFUtility.h"

float WFUtility::DegToRad(float deg)
{
	return std::move(deg * DX_PI_F / 180);
}

double WFUtility::DegToRad(double deg)
{
	return std::move(deg * DX_PI / 180);
}

float WFUtility::RadToDeg(float deg)
{
	return std::move(deg * (180 / DX_PI_F));
}

double WFUtility::RadToDeg(double deg)
{
	return std::move(deg * (180 / DX_PI));
}

Vector2 WFUtility::VecFltToVecInt(Vector2flt vec)
{
	return std::move(Vector2(static_cast<int>(vec.x), static_cast<int>(vec.y)));
}

Vector2 WFUtility::VecDblToVecInt(Vector2dbl vec)
{
	return std::move(Vector2(static_cast<int>(vec.x), static_cast<int>(vec.y)));
}

Vector2flt WFUtility::VecIntToVecFlt(Vector2 vec)
{
	return std::move(Vector2flt(static_cast<float>(vec.x), static_cast<float>(vec.y)));
}

Vector2flt WFUtility::VecDblToVecFlt(Vector2dbl vec)
{
	return std::move(Vector2flt(static_cast<float>(vec.x), static_cast<float>(vec.y)));
}

Vector2dbl WFUtility::VecIntToVecDbl(Vector2 vec)
{
	return std::move(Vector2dbl(static_cast<float>(vec.x), static_cast<float>(vec.y)));
}

Vector2dbl WFUtility::VecFltToVecDbl(Vector2flt vec)
{
	return std::move(Vector2dbl(static_cast<float>(vec.x), static_cast<float>(vec.y)));
}
