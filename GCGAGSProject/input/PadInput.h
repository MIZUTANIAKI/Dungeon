#pragma once
#include <vector>
#include "Controller.h"
#include "Vector2.h"

class PadInput :
	public Controller
{
public:
	ContType GetType(void)override;

	bool Setup()override;

	void Update()override;
	PadInput();
	~PadInput();
private:

	Vector2 _pos;
	std::map<InputID, int> _inputTblANAROG;
	std::map<InputID, bool> _keymap;

	bool padPlugIn_;
};