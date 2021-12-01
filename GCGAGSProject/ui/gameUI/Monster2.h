#pragma once
#include "ScrollUIBase.h"
class Monster2 :
    public ScrollUIBase
{
public:
	Monster2();
	Monster2(Vector2 pos);
	~Monster2();

	void Update(void) override;
	void Draw(void) override;
private:
	void Init()  override;
};

