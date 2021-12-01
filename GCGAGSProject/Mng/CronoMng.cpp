#include "CronoMng.h"

CronoMng* CronoMng::sInstance = nullptr;

void CronoMng::Start()
{
	start_ = std::chrono::system_clock::now();
}

void CronoMng::Last()
{
	deltaTime_ = std::chrono::duration_cast<std::chrono::microseconds>(start_ - end_).count() / 1000000.0f;
	end_ = start_;

}

CronoMng::CronoMng()
{
	deltaTime_ = 0.0f;
	end_ = start_ = std::chrono::system_clock::now();
}

CronoMng::~CronoMng()
{
}
