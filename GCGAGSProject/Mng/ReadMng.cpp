#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <DxLib.h>
#include "ReadMng.h"

ReadMng* ReadMng::sInstance = nullptr;

int ReadMng::GetDate(setinglist set)noexcept
{
	if (bright_ == -1)
	{
		OpenFile();
	}
	if (set == setinglist::Bright)
	{
		return bright_;
	}
	if (set == setinglist::SoundVol)
	{
		return soundVol_;
	}
	return 255;
}

void ReadMng::SetDate(setinglist set, int num)
{
	if (set == setinglist::Bright)
	{
		bright_ = num;
	}
	if (set == setinglist::SoundVol)
	{
		soundVol_ = num;
	}
	if (set == setinglist::Money)
	{
		money_ = num;
	}

	std::ofstream ofs;
	ofs.open("MySetting/seting.txt", std::ios::out);

	ofs << bright_;
	ofs << ",";
	ofs << soundVol_;
	ofs << ",";
	ofs << money_;
	ofs.close();
}

void ReadMng::OpenFile()
{
	std::string tstr = "MySetting/seting.txt";
	std::ifstream ifs(tstr);
	if (!ifs)
	{
		tstr = "resource\\date/seting.txt";
		ifs.open(tstr);
		if (!ifs)
		{
			MessageBox(NULL, "ファイルオープン失敗", "", MB_OK);
			return;
		}
	}

	std::string readStr;
	std::vector<std::string> stringVector;

	while (!ifs.eof())
	{
		std::getline(ifs, readStr);
		if (readStr == "")
		{
			return;
		}
		std::string tmpStr;
		std::istringstream iss(readStr);
		int dcon = 0;
		do
		{
			std::getline(iss, tmpStr, ',');
			if (dcon == 0)
			{
				bright_ = atoi(tmpStr.c_str());
			}
			if (dcon == 1)
			{
				soundVol_ = atoi(tmpStr.c_str());
			}
			if (dcon == 2)
			{
				money_ = atoi(tmpStr.c_str());
			}
			dcon++;
		} while (!iss.eof());
	}
}

ReadMng::ReadMng()
{
	soundVol_ = -1;
	bright_ = -1;
}

ReadMng::~ReadMng()
{
}