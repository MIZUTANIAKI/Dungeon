#pragma once

class FPSKeeper
{

public:
	FPSKeeper();
	~FPSKeeper();

	bool Update(void);

	void Draw();

	void Wait(void);
private:
	void Init(void);

	int firstTime_;
	int timeCount;
	float nowFps_;
	const int setFps_;
};

