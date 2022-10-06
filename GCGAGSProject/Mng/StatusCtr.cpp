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
	DelDate();
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
	statusMap_.try_emplace(StatusID::Stage, 1);
}

void StatusCtr::InputD(void)
{
	if (statusMap_.size() !=8)
	{
		DelDate();
	}
	std::string tstr = "savedate/PlayerDat.txt";
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
				statusMap_[StatusID::MapSize]=atoi(tmpStr.c_str());
			}
			if (dcon == 1)
			{
				statusMap_[StatusID::Monster1] = atoi(tmpStr.c_str());
			}
			if (dcon == 2)
			{
				statusMap_[StatusID::Monster2] = atoi(tmpStr.c_str());
			}
			if (dcon == 3)
			{
				statusMap_[StatusID::Monster3] = atoi(tmpStr.c_str());
			}
			if (dcon == 4)
			{
				statusMap_[StatusID::GImmick1] = atoi(tmpStr.c_str());
			}
			if (dcon == 5)
			{
				statusMap_[StatusID::GImmick2] = atoi(tmpStr.c_str());
			}
			if (dcon == 6)
			{
				statusMap_[StatusID::PlayerHP] = atoi(tmpStr.c_str());
			}
			if (dcon == 7)
			{
				statusMap_[StatusID::Stage] = atoi(tmpStr.c_str());
			}
			dcon++;
		} while (!iss.eof());
	}
}

