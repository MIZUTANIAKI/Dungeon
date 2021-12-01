#pragma once
#include "GraphNode.h"
#include "MapMng.h"
#include "Vector2.h"


class NavGraphNode:
	public GraphNode
{
public:
	NavGraphNode() {};
	~NavGraphNode() = default;

	Vector2 GetPosition(void)
	{
		return positon_;
	}
	void SetPosition(Vector2 pos)
	{
		positon_ = pos;
	}
protected:
	//�m�[�h�̏ꏊ
	Vector2 positon_;
};
