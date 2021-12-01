#include "Controller.h"

Controller::Controller()
{
	padData_ = DINPUT_JOYSTATE();
}

Controller::~Controller()
{
}