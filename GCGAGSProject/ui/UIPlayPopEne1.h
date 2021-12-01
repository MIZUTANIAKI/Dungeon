#pragma once
#include "UIBase.h"
class UIPlayPopEne1 :
    public UIBase
{
public:
	UIPlayPopEne1();
	UIPlayPopEne1(Vector2 pos, Vector2 size);
	~UIPlayPopEne1();

	void Update(void)override;
	void SetDate(void)override;
	void Draw(void)override;

private:

	int subUi_;
	bool subUIDispF_;
	int mousecount_;
};

