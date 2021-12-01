#pragma once
#include "ScrollUIBase.h"
class Monster3 :
    public ScrollUIBase
{
public:
	Monster3();
	Monster3(Vector2 pos);
	~Monster3();

	void Update(void) override;
	void Draw(void) override;
private:
	void Init()  override;
};

