#pragma once
#include <array>
#include <map>
#include <DxLib.h>
#include "inputID.h"

enum class ContType
{
	Key,
	MouseInput,
	Pad,
	Np,
	Max
};

enum class Trg
{
	Now,
	Old,
	Max
};

using TrgBool = std::array<bool, static_cast<size_t>(Trg::Max)>;
using ControllerData = std::map<InputID, TrgBool>;

class Controller
{
public:

	const DINPUT_JOYSTATE& GetPadDeta(void)const noexcept
	{
		return padData_;
	}

	const ControllerData& GetControllerData(void)const noexcept
	{
		return data_;
	}
	const bool GetControllerData(InputID id)noexcept
	{
		if (data_[id][static_cast<int>(Trg::Now)] == true)
		{
			return true;
		}
		return false;
	}
	const bool GetControllerData(InputID id, int num)noexcept
	{
		if (data_[id][static_cast<int>(Trg::Old)] != true && data_[id][static_cast<int>(Trg::Now)] == true)
		{
			return true;
		}
		return false;
	}
	virtual ContType GetType(void) = 0;

	virtual bool Setup() = 0;
	Controller();
	virtual ~Controller();
	virtual void Update() = 0;

private:

protected:
	ControllerData data_;
	DINPUT_JOYSTATE  padData_;
};