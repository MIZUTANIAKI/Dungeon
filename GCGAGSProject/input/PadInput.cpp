#include <DxLib.h>
#include "PadInput.h"

ContType PadInput::GetType(void)
{
	return ContType::Pad;
}

bool PadInput::Setup()
{
	JOYINFOEX JoyInfoEx;
	for (unsigned int i = 0; i < joyGetNumDevs(); i++)
	{
		if (JOYERR_NOERROR == joyGetPosEx(i, &JoyInfoEx))
		{
			ReSetupJoypad();
			padPlugIn_ = true;
			return true;
		}
	}
	//ReSetupJoypad();
	//int a = GetJoypadNum();
	//if (a == 0)
	//{
	//}

	//padPlugIn_ = GetJoypadXInputState(DX_INPUT_PAD1, &padData_) == 0 ? true : false;

	SetJoypadDeadZone(DX_INPUT_PAD1, 0.3);
	//StartJoypadVibration(_padNum, 1000, 30);
	return false;
}

void PadInput::Update()
{
	for (auto& km : _keymap)
	{
		km.second = false;
	}

	padPlugIn_ = GetJoypadDirectInputState(DX_INPUT_PAD1, &padData_) == 0 ? true : false;
	if (!padPlugIn_)
	{
		padPlugIn_ = false;
		if (!Setup())
		{
			return;
		}
	}

	//Lスティック
	if (abs(padData_.X) > 500)
	{
		if (padData_.X > 500)
		{
			_keymap[InputID::LSRight] = true;
		}
		else
		{
			_keymap[InputID::LSLeft] = true;
		}
	}
	if (abs(padData_.Y) > 500)
	{
		if (padData_.Y > 500)
		{
			_keymap[InputID::LSDown] = true;
		}
		else
		{
			_keymap[InputID::LSUp] = true;
		}
	}
	//Rスティック
	if (abs(padData_.Rx) > 500)
	{
		if (padData_.Rx > 500)
		{
			_keymap[InputID::RSRight] = true;
		}
		else
		{
			_keymap[InputID::RSLeft] = true;
		}
	}
	if (abs(padData_.Rz) > 500)
	{
		if (padData_.Rz > 500)
		{
			_keymap[InputID::RSDown] = true;
		}
		else
		{
			_keymap[InputID::RSUp] = true;
		}
	}

	//トリガー
	if (abs(padData_.Z) > 500)
	{
		if (padData_.Z > 500)
		{
			_keymap[InputID::LT] = true;
		}
		else
		{
			_keymap[InputID::RT] = true;
		}
	}

	//ボタン情報
	for (auto btnD : _inputTblANAROG)
	{
		if (padData_.Buttons[btnD.second] == 128)
		{
			_keymap[btnD.first] = true;
		}
	}

	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP) != 0)
	{
		_keymap[InputID::Up] = true;
	}
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT) != 0)
	{
		_keymap[InputID::Right] = true;
	}
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN) != 0)
	{
		_keymap[InputID::Down] = true;
	}
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT) != 0)
	{
		_keymap[InputID::Left] = true;
	}

	for (auto id : InputID())
	{
		data_[id][static_cast<int>(Trg::Old)] = data_[id][static_cast<int>(Trg::Now)];
		data_[id][static_cast<int>(Trg::Now)] = _keymap[id] == true ? true : false;
	}
}

PadInput::PadInput()
{
	padPlugIn_ = GetJoypadDirectInputState(DX_INPUT_PAD1, &padData_) == 0 ? true : false;

	_inputTblANAROG = {
		{InputID::BtnA,0},
		{InputID::BtnB,1},
		{InputID::BtnX,2},
		{InputID::BtnY,3},
		{InputID::LB,4},
		{InputID::RB,5},
		{InputID::LS,8},
		{InputID::RS,9},
		{InputID::View,6},
		{InputID::Menu,7},
	};
	_keymap = {
		{InputID::Up,false},
		{InputID::Right,false},
		{InputID::Down,false},
		{InputID::Left,false},
		{InputID::BtnA,false},
		{InputID::BtnB,false},
		{InputID::BtnX,false},
		{InputID::BtnY,false},
		{InputID::LB,false},
		{InputID::LT,false},
		{InputID::RB,false},
		{InputID::RT,false},
		{InputID::LS,false},
		{InputID::RS,false},
		{InputID::LSUp,false},
		{InputID::LSRight,false},
		{InputID::LSDown,false},
		{InputID::LSLeft,false},
		{InputID::RSUp,false},
		{InputID::RSRight,false},
		{InputID::RSDown,false},
		{InputID::RSLeft,false},
		{InputID::View,false},
		{InputID::Menu,false},
	};
}

PadInput::~PadInput()
{
}