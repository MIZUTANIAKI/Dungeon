#pragma once
#include "UIBase.h"
class UIBackPlay :
    public UIBase
{
public:
	UIBackPlay();
	UIBackPlay(Vector2 pos, Vector2 size);
	~UIBackPlay();

	void Update(void)override;
	void SetDate(void)override;
	void Draw(void)override;

private:

	int subUi_;
	bool subUIDispF_;
	int mousecount_;
	int fcon_;
};

