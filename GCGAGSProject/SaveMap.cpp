#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "SaveMap.h"
#include "Spike.h"
#include "Gate.h"
#include "common/Vector2.h"

SaveMap::SaveMap()
{
}

SaveMap::~SaveMap()
{
}

void SaveMap::StartOutPut(int num)
{
	if (mapdat_.empty())
	{
		return;
	}

	std::ofstream ofs;
	std::string fname = "savedate/savemap_";
	fname = fname + std::to_string(num) + ".gmp";
	ofs.open(fname, std::ios::out);
	Vector2 mapSize = Vector2(static_cast<int>(mapdat_[0].size()), static_cast<int>(mapdat_.size()));
	for (int y = 0; y < mapSize.y; y++)
	{
		for (int x = 0; x < mapSize.x; x++)
		{
			if (mapdat_[y][x] == BlockDate::Block)
			{
				ofs << 0;
			}
			if (mapdat_[y][x] == BlockDate::Road)
			{
				ofs << 1;
			}
			if (mapdat_[y][x] == BlockDate::Start)
			{
				ofs << 2;
			}
			if (mapdat_[y][x] == BlockDate::Goal)
			{
				ofs << 3;
			}
			if (x != mapSize.x - 1)
			{
				ofs << ",";
			}
		}
		if (y != mapSize.y - 1)
		{
			ofs << std::endl;
		}
	}
	ofs.close();

	//if (dateBox_.empty())
	//{
	//	ofs.open("savedate/saveMPos.gdt", std::ios::out);
	//	ofs << std::endl;
	//	return;
	//}
	//ofs.open("savedate/saveMPos.gdt", std::ios::out);
	//int con = 0;
	//for (auto& dat : dateBox_)
	//{
	//	if (dat->GetObjectID() == ObjectID::Spike)
	//	{
	//		ofs << 1;
	//	}
	//	if (dat->GetObjectID() == ObjectID::Gate)
	//	{
	//		ofs << 2;
	//	}
	//	ofs << ",";
	//	ofs << dat->GetDefPos().x;
	//	ofs << ",";
	//	ofs << dat->GetDefPos().y;
	//	con++;
	//	if (con != dateBox_.size())
	//	{
	//		ofs << std::endl;
	//	}
	//}
}

void SaveMap::StartInPut(int num)
{
	std::ifstream ifs;
	std::string fname = "savedate/savemap_";
	fname = fname + std::to_string(num) + ".gmp";
	ifs.open(fname, std::ios::in);

	std::string readStr;
	size_t y, x;
	y = x = 0;
	while (!ifs.eof())
	{
		mapdat_.resize(y + 1);

		std::getline(ifs, readStr);
		x = 0;
		std::string tmpStr;
		std::istringstream iss(readStr);
		do
		{
			std::getline(iss, tmpStr, ',');

			if (atoi(tmpStr.c_str()) == 0)
			{
				mapdat_[y].emplace_back(BlockDate::Block);
			}
			if (atoi(tmpStr.c_str()) == 1)
			{
				mapdat_[y].emplace_back(BlockDate::DRoad);
			}
			if (atoi(tmpStr.c_str()) == 2)
			{
				mapdat_[y].emplace_back(BlockDate::Start);
			}
			if (atoi(tmpStr.c_str()) == 3)
			{
				mapdat_[y].emplace_back(BlockDate::Goal);
			}

		} while (!iss.eof());
		y++;
	}
	ifs.close();
	ifs.open("savedate/saveMPos.gdt", std::ios::in);
}

