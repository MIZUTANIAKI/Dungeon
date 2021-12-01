#pragma once
#include "NavGraphNode.h"

class GraphEdge
{
public:
	GraphEdge(int flom, int to, double cost) : iFrom_(flom), iTo_(to), dCost_(cost) { dNode_ = -1; };
	GraphEdge(int flom, int to) : iFrom_(flom), iTo_(to), dCost_(1.0) { dNode_ = -1; };
	GraphEdge() : iFrom_(invalid_node_index), iTo_(invalid_node_index), dCost_(1.0) { dNode_ = -1; };

	virtual ~GraphEdge() = default;

	int From()const { return iFrom_; };
	void SetFrom(int newIndex) { iFrom_ = newIndex; };

	int To()const { return iTo_; };
	void SetTo(int newIndex) { iTo_ = newIndex; };

	int Cost()const { return static_cast<int>(dCost_);; };
	void SetCost(int newCost) { dCost_ = newCost; };

	int Node()const { return dNode_; };
	void SetNode(int newNode) { dNode_ = newNode; };
protected:
	int iFrom_;	//自分の前のノード
	int iTo_;	//自分の次のノード

	double dCost_;	//コスト
	int dNode_;		//訪れたノード

};

