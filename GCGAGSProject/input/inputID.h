#pragma once

enum class InputID {
	Up,
	Right,
	Down,
	Left,
	BtnA,
	BtnB,
	BtnX,
	BtnY,
	LB,
	LT,
	RB,
	RT,
	LS,
	RS,
	LSUp,
	LSRight,
	LSDown,
	LSLeft,
	RSUp,
	RSRight,
	RSDown,
	RSLeft,
	View,
	Menu,
	Max
};

static InputID begin(InputID) { return InputID::Up; }
static InputID end(InputID) { return InputID::Max; }
static InputID operator++(InputID& state) { return state = static_cast<InputID>(std::underlying_type<InputID>::type(state) + 1); }
static InputID operator*(InputID state) { return state; }
