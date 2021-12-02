#include <vector>
#include <array>
#include <stdio.h>
#include <map>
#include <string>
#include <algorithm>
#include <DxLib.h>
#include "ImageMng.h"

ImageMng* ImageMng::sInstance = nullptr;

void ImageMng::DrawNaw(void)
{
	stable_sort(drawList_.begin(), drawList_.end(), [](auto& x, auto& y) {
		return x.first.second < y.first.second;
		});

	stable_sort(drawList_.begin(), drawList_.end(), [](auto& x, auto& y) {
		if (x.first.second == y.first.second)
		{
			return x.second.y < y.second.y;
		}
		return false;
		});

	for (auto itr = drawList_.begin(); itr != drawList_.end(); itr++)
	{
		if ((30 <= itr->first.second && itr->first.second <= 39) || (70 <= itr->first.second && itr->first.second <= 79))
		{
			SetDrawBright(255, 255, 255);
			DrawGraph(itr->second.x, itr->second.y, itr->first.first, true);
		}
		else
		{
			SetDrawBright(bright_, bright_, bright_);
			DrawGraph(itr->second.x, itr->second.y, itr->first.first, true);
		}
	}
}

void ImageMng::ReSetD(void)
{
	drawList_.clear();
}

void ImageMng::GraphAddDrawQue(std::string id, Vector2 pos, int z)
{
	drawList_.emplace_back(std::pair<std::pair<int, int>, Vector2>(std::pair<int, int>(GetGraphHandle(id), z), pos));
}

void ImageMng::ScreenAddDrawQue(int id, int z)
{
	drawList_.emplace_back(std::pair<std::pair<int, int>, Vector2>(std::pair<int, int>(id, z), Vector2(0, 0)));
}

void ImageMng::ScreenAddDrawQue(int id, Vector2 pos, int z)
{
	drawList_.emplace_back(std::pair<std::pair<int, int>, Vector2>(std::pair<int, int>(id, z), pos));
}

std::string ImageMng::LoadGraph(std::string fileName)
{
	if (GetGraphHandle(fileName) == -1)
	{
		std::string tstr = "resource\\img/";
		tstr += fileName;
		imgList_.try_emplace(fileName, DxLib::LoadGraph(tstr.c_str()));
	}
	return fileName;
}

void ImageMng::DeleteGraph(std::string id)
{
	imgList_.erase(id);
}

void ImageMng::ReSetDate(void)
{
	imgList_.clear();
}

int ImageMng::GetGraphHandle(std::string id)
{
	if (imgList_.find(id) == imgList_.end())
	{
		std::string tstr = "resource\\img/";
		tstr += id;
		imgList_.try_emplace(id, DxLib::LoadGraph(tstr.c_str()));
	}
	return imgList_.at(id);
}

void ImageMng::SetBright(int num)
{
	bright_ = min(max(0, num), 255);
	SetDrawBright(bright_, bright_, bright_);
}

void ImageMng::DrawImg(std::string name, Vector2 pos)
{
	DrawGraph(pos.x, pos.y, lpImglMng.GetGraphHandle(name), true);
}

ImageMng::ImageMng()
{
	bright_ = 255;
	screenSize_.x = 0;
	screenSize_.y = 0;
	GetDrawScreenSize(&screenSize_.x, &screenSize_.y);
}

ImageMng::~ImageMng()
{
}