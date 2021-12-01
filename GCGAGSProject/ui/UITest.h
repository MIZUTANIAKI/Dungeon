#pragma once
#include "UIBase.h"

class UITest :
    public UIBase
{
public:
	UITest();
	UITest(Vector2 pos, Vector2 size);
	~UITest();

	void Update(void)override;
	void SetDate(void)override;
	void Draw(void)override;
private:
	Vector2 mouseSubpos_;

	UNUI subUi_;
	bool subUIDispF_;
	bool grabF_;
	int mousecount_;
};

