#pragma once
#include "UIBase.h"
class UIPlayPopEne2 :
    public UIBase
{
public:
	UIPlayPopEne2();
	UIPlayPopEne2(Vector2 pos, Vector2 size);
	~UIPlayPopEne2();

	void Update(void)override;
	void SetDate(void)override;
	void Draw(void)override;

private:

	int subUi_;
	bool subUIDispF_;
	int mousecount_;
};

