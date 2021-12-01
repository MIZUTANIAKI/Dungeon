#pragma once
#include "Explorer.h"
class Gate :
	public Explorer
{
public:
	Gate();
	~Gate() override;
	void Update(void)override;
	void Draw()override;
	void Init()override;
private:
	void Damage(Explorer& target)override;
};
