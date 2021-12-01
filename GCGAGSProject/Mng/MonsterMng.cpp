#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <DxLib.h>
#include "MonsterMng.h"
#include "Vector2.h"

MonsterMng* MonsterMng::sInstance = nullptr;

void MonsterMng::StartOutPut()
{
	std::ofstream ofs;
	ofs.open("savedate/monster.gdt", std::ios::out);
	ofs << slime_.first;
	ofs << ',';
	ofs << slime_.second;
	ofs << std::endl;
	ofs << desmodus_.first;
	ofs << ',';
	ofs << desmodus_.second;
	ofs << std::endl;
	ofs << rook_.first;
	ofs << ',';
	ofs << rook_.second;
	ofs << std::endl;
	ofs << Onibi_.first;
	ofs << ',';
	ofs << Onibi_.second;
	return;
}

void MonsterMng::StartInPut()
{
	std::ifstream ifs;
	std::string readStr;
	ifs.open("savedate/monster.gdt", std::ios::in);
	if (!ifs)
	{
		readStr = "resource\\date/seting.txt";
		ifs.open(readStr);
		if (!ifs)
		{
			MessageBox(NULL, "ファイルオープン失敗", "", MB_OK);
			return;
		}
	}

	int count = 0;
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
		int hp = 0;
		int atk = 0;
		do
		{
			std::getline(iss, tmpStr, ',');
			if (dcon == 0)
			{
				hp = atoi(tmpStr.c_str());
			}
			if (dcon == 1)
			{
				atk = atoi(tmpStr.c_str());
			}
			dcon++;
		} while (!iss.eof());

		if (count == 0)
		{
			slime_.first = static_cast<float>(hp);
			slime_.second = static_cast<float>(atk);
		}
		if (count == 1)
		{
			desmodus_.first = static_cast<float>(hp);
			desmodus_.second = static_cast<float>(atk);
		}

		if (count == 2)
		{
			rook_.first = static_cast<float>(hp);
			rook_.second = static_cast<float>(atk);
		}

		if (count == 3)
		{
			Onibi_.first = static_cast<float>(hp);
			Onibi_.second = static_cast<float>(atk);
		}
		count++;
	}
}

std::pair<float, float> MonsterMng::StartInPutAdven(int num)
{
	if (adventurerMap_.empty())
	{
		InputAdven();
	}
	if (adventurerMap_.find(num) == adventurerMap_.end())
	{
		return std::pair<float, float>();
	}

	return adventurerMap_.at(num);
}

void MonsterMng::InputAdven()
{
	std::pair<float, float> adventurer_;

	std::ifstream ifs;
	std::string readStr;
	ifs.open("savedate/adven.gdt", std::ios::in);

	int count = 1;
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
		int hp = 0;
		int atk = 0;
		do
		{
			std::getline(iss, tmpStr, ',');
			if (dcon == 0)
			{
				hp = atoi(tmpStr.c_str());
			}
			if (dcon == 1)
			{
				atk = atoi(tmpStr.c_str());
			}
			dcon++;
		} while (!iss.eof());

		adventurer_.first = static_cast<float>(hp);
		adventurer_.second = static_cast<float>(atk);
		adventurerMap_.try_emplace(count, std::pair<float, float>(adventurer_.first, adventurer_.second));
		count++;
	}
}

MonsterMng::MonsterMng()
{
	slime_ = { 0.0f ,0.0f };
	desmodus_ = { 0.0f ,0.0f };
	rook_ = { 0.0f ,0.0f };
	Onibi_ = { 0.0f ,0.0f };
}

MonsterMng::~MonsterMng()
{
}