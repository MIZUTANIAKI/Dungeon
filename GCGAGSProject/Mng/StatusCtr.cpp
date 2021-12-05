#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "StatusCtr.h"

std::map<StatusID, int> StatusCtr::statusMap_;

int StatusCtr::GetStates(StatusID id)
{
	if (statusMap_.find(id) == statusMap_.end())
	{
		return 0;
	}
	return statusMap_[id];
}

void StatusCtr::SetStates(StatusID id, int num)
{
	if (statusMap_.find(id) == statusMap_.end())
	{
		statusMap_.try_emplace(id, num);
		return;
	}
	statusMap_[id] = num;
}

void StatusCtr::Reset(void)
{
    statusMap_.clear();
	InputD();
}

void StatusCtr::OutPutD(void)
{
    std::ofstream ofs;
    ofs.open("savedate/PlayerDat.txt", std::ios::out);

    for (const auto& status : statusMap_)
    {
        ofs << status.second;
        ofs << ",";
    }
    ofs.close();
}

void StatusCtr::DelDate(void)
{
	statusMap_.try_emplace(StatusID::MapSize, 0);
	statusMap_.try_emplace(StatusID::Monster1, 1);
	statusMap_.try_emplace(StatusID::Monster2, 1);
	statusMap_.try_emplace(StatusID::Monster3, 1);
	statusMap_.try_emplace(StatusID::GImmick1, 1);
	statusMap_.try_emplace(StatusID::GImmick2, 1);
	statusMap_.try_emplace(StatusID::PlayerHP, 10);
}

void StatusCtr::InputD(void)
{
	std::string tstr = "MySetting/PlayerDat.txt";
	std::ifstream ifs(tstr);
	if (!ifs)
	{
		return;
	}

	std::string readStr;

	while (!ifs.eof())
	{
		std::getline(ifs, readStr);
		if (readStr == "")
		{
			DelDate();
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
				statusMap_.try_emplace(StatusID::MapSize, atoi(tmpStr.c_str()));
			}
			if (dcon == 1)
			{
				statusMap_.try_emplace(StatusID::Monster1, atoi(tmpStr.c_str()));
			}
			if (dcon == 2)
			{
				statusMap_.try_emplace(StatusID::Monster1, atoi(tmpStr.c_str()));
			}
			if (dcon == 3)
			{
				statusMap_.try_emplace(StatusID::Monster2, atoi(tmpStr.c_str()));
			}
			if (dcon == 4)
			{
				statusMap_.try_emplace(StatusID::Monster3, atoi(tmpStr.c_str()));
			}
			if (dcon == 5)
			{
				statusMap_.try_emplace(StatusID::GImmick1, atoi(tmpStr.c_str()));
			}
			if (dcon == 6)
			{
				statusMap_.try_emplace(StatusID::GImmick2, atoi(tmpStr.c_str()));
			}
			if (dcon == 6)
			{
				statusMap_.try_emplace(StatusID::PlayerHP, atoi(tmpStr.c_str()));
			}
			dcon++;
		} while (!iss.eof());
	}
}

