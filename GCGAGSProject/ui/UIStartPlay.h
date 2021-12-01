#pragma once
#include "UIBase.h"

class UIStartPlay :
	public UIBase
{
public:
	UIStartPlay();
	UIStartPlay(Vector2 pos, Vector2 size);
	~UIStartPlay();

	void Update(void)override;
	void SetDate(void)override;
	void Draw(void)override;

private:

	int subUi_;
	bool subUIDispF_;
	int mousecount_;
	int fcon_;
};

