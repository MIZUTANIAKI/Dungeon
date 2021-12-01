#pragma once
#include <memory>
#include "Controller.h"

#define lpPadMng PadMng::GetInstance()

class Controller;

class PadMng
{
public:
	static PadMng& GetInstance(void)
	{
		Create();
		return *sInstance;
	}

	static void Create()
	{
		if (sInstance == nullptr)
		{
			sInstance = new PadMng();
		}
	}

	static void Destroy()
	{
		if (sInstance != nullptr)
		{
			delete sInstance;
		}
		sInstance = nullptr;
	}
	
	bool IsPlugInForGamePad(void) const noexcept
	{
		return padPlugIn_;
	}

	void Update(void);

	void MovePos();

	const DINPUT_JOYSTATE& GetPadDeta(void) const noexcept
	{
		return controller_->GetPadDeta();
	}

	const ControllerData& GetControllerData(void) const noexcept
	{
		return controller_->GetControllerData();
	}
	const bool GetNowControllerData(InputID id) const noexcept
	{
		return controller_->GetControllerData(id);
	}
	const bool GetControllerData(InputID id) const noexcept
	{
		return controller_->GetControllerData(id, 0);
	}

private:
	static PadMng* sInstance;

	std::unique_ptr< Controller> controller_;

	PadMng();
	~PadMng();

	bool padPlugIn_;
};
