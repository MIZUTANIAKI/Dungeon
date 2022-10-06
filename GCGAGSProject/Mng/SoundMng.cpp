#include <DxLib.h>
#include "SoundMng.h"

SoundMng* SoundMng::sInstance = nullptr;

void SoundMng::LoadSound(std::string fileName)
{
	if (GetSoundHandle(fileName) == -1)
	{
		std::string tstr = "resource\\se/";
		tstr += fileName;
		int sh = DxLib::LoadSoundMem(tstr.c_str());
		ChangeVolumeSoundMem(soundVol_, sh);
		soundList_.try_emplace(fileName, sh);
	}
}

void SoundMng::SoundPlay(std::string id, int PlayType)
{
	PlaySoundMem(GetSoundHandle(id), PlayType);
}

void SoundMng::DirectSoudPlay(int id, int PlayType)
{
	PlaySoundMem(id, PlayType);
}

bool SoundMng::CheckPlaySound(std::string id)
{
	if (CheckSoundMem(GetSoundHandle(id)) == 1)
	{
		return true;
	}
	return false;
}

void SoundMng::StopSound(std::string id)
{
	StopSoundMem(GetSoundHandle(id));
}

void SoundMng::DeleteSound(std::string id)
{
	soundList_.erase(id);
}

void SoundMng::ReSetDate(void)
{
	soundList_.clear();
}

int SoundMng::GetSoundHandle(std::string id)
{
	if (soundList_.find(id) == soundList_.end())
	{
		return -1;
		//std::string tstr = "resource\\se/";
		//tstr += id;
		//soundList_.try_emplace(id, DxLib::LoadGraph(tstr.c_str()));
	}
	return soundList_.at(id);
}

void SoundMng::SetSoundVol(int num)
{
	soundVol_ = min(max(num, 0), 255);
	for (auto& sf : soundList_)
	{
		ChangeVolumeSoundMem(soundVol_, sf.second);
	}
}

SoundMng::SoundMng()
{
	soundVol_ = 255;
}

SoundMng::~SoundMng()
{
}