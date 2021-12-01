#pragma once
#include "ScrollUIBase.h"

class Monster1 :
    public ScrollUIBase
{
public:
	Monster1();
	Monster1(Vector2 pos);
	~Monster1();

	void Update(void) override;
	void Draw(void) override;
private:
	void Init()  override;
};

