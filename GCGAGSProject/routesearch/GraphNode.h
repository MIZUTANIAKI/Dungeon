#pragma once
#include "NodeType.h"

class GraphNode
{
public:
	GraphNode() :iIndex_(invalid_node_index) {};
	GraphNode(int idx) :iIndex_(idx) {}

	virtual ~GraphNode() = default;
	int Index()const 
	{
		return iIndex_; 
	};
	void SetIndex(int NewIndex) 
	{
		iIndex_ = NewIndex;
	};

	int Cost()const { return static_cast<int>(dCost_);; };
	void SetCost(int newCost) { dCost_ = newCost; };
	int Node()const { return dNode_; };
	void SetNode(int newNode) { dNode_ = newNode; };
	void Reset() 
	{
		dCost_ = 0;
		dNode_ = -1;
	}
protected:
	//ノード番号
	int iIndex_;
	double dCost_ = -1;	//コスト
	int dNode_ = -1;	//訪れたノード
};

