#pragma once
#include "UIBase.h"

class UISubTest :
    public UIBase
{
public:
	UISubTest();
	UISubTest(Vector2 pos, Vector2 size);
	~UISubTest();

	void Update(void)override;
	void SetDate(void)override;
	void SetDate(std::string str) override;
	void Draw(void)override;
private:
	std::string drawDate_;
};

