#include "SparseGraph.h"

int SparseGraph::AddNode(NavGraphNode node)
{
	//ノードがサイズより大きいかどうか
	if (node.Index() < static_cast<int>(nodes_.size()))
	{
		//小さい場合、そのまま探す。次のノードのインデックスを送る

		//assert(nodes_[node.Index()].Index() == invalid_node_index && "SparseGraphクラス[AddNode]");
		nodes_[node.Index()] = node;
		return iNextNodeIndex_;
	}
	else
	{
		//大きい場合、追加する、次のノードのインデックスを送る
		//assert(node.Index() == iNextNodeIndex_ && "SparseGraphクラス[AddNode]");
		nodes_.push_back(node);
		edges_.push_back(EdgeList());
		return iNextNodeIndex_++;
	}
}

void SparseGraph::AddEdge(GraphEdge edge)
{
	//値が、未設定だったらここで終了する
	if ((nodes_[edge.To()].Index() == invalid_node_index) || (nodes_[edge.From()].Index() == invalid_node_index))
	{
		return;
	}
	bool itrCheck = false;
	//同じ前ノードで、同じ行先があるか
	for (auto edgeItr = edges_[edge.From()].begin(); edgeItr != edges_[edge.From()].end(); ++edgeItr)
	{
		if (edgeItr->To() == edge.To())
		{
			itrCheck = true;
		}
	}
	if (!itrCheck)
	{
		edges_[edge.From()].push_back(edge);
	}

	if (bDigraph_)
	{
		//有向グラフの場合ここで終了
		return;
	}

	//同じ行先ノードで、同じ前ノードがあるか
	itrCheck = false;
	for (auto edgeItr = edges_[edge.To()].begin(); edgeItr != edges_[edge.To()].end(); ++edgeItr)
	{
		if (edgeItr->To() == edge.From())
		{
			itrCheck = true;
		}
	}
	if (itrCheck)
	{
		return;
	}

	// 新しいエッジを作成（このエッジは上記でpush_backしたエッジと対になるエッジである）
	GraphEdge NewEdge = edge;
	NewEdge.SetTo(edge.From());
	NewEdge.SetFrom(edge.To());
	edges_[edge.To()].push_back(NewEdge);
}

