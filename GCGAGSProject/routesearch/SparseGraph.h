#pragma once
#include <cassert>
#include <iostream>
#include <vector>
#include <list>
#include "GraphNode.h"
#include "GraphEdge.h"
#include "NavGraphNode.h"


class SparseGraph
{
public:
	typedef std::vector<NavGraphNode> NodeVector;
	typedef std::list<GraphEdge> EdgeList;
	typedef std::vector<EdgeList> EdgeListVector;
public:
	SparseGraph(bool digraph) :iNextNodeIndex_(0), bDigraph_(digraph) {}

	//ノードを追加する
	int AddNode(NavGraphNode node);

	//エッジを追加する
	void AddEdge(GraphEdge edge);

	//グラフ内のノード数を返す
	int NumNodes()const 
	{ 
		return static_cast<int>(nodes_.size());
	}

	//これは有向グラフであるか
	bool IsDigraph()const 
	{ 
		return bDigraph_; 
	}

	//グラフ内にノードが存在するか
	bool IsEmpty()const 
	{ 
		return nodes_.empty();
	}

	//Edgeを取得する
	EdgeListVector GetEdges()const { return edges_; }

	//次のフリーノードのインデックスを取得する。
	int GetNextFreeNodeIndex()const { return iNextNodeIndex_; }

	//初期化
	void Clear()
	{
		nodes_.clear();
		edges_.clear();
		bDigraph_ = false;
		iNextNodeIndex_ = invalid_node_index;
	};

	//// グラフクラスが持つ list配列 や vector配列 へのアクセスを容易にするイテレータクラス
	//class EdgeIterator
	//{
	//private:
	//	EdgeList::const_iterator edgeListItr_;
	//public:
	//	EdgeIterator(const SparseGraph& graph, int node);
	//	const GraphEdgh* begin();
	//	const GraphEdgh* next();
	//	bool end();
	//private:
	//	const SparseGraph& graph_;
	//	const int nodeIndex_;
	//};

private:
	//グラフを構成するノード
	NodeVector nodes_;
	//隣接エッジのベクター
	//（各ノードのインデックスは、そのノードに関連付けられたエッジのリストのキーになる）
	EdgeListVector edges_;
	//グラフは有向グラフであるかどうか
	bool bDigraph_;
	//次に追加されるノードのインデックス
	int iNextNodeIndex_;


//	//グラフを構成するノード
//	NodeVector nodes_;
//
//	//隣接エッジのベクター
//	//（各ノードのインデックスは、そのノードに関連付けられたエッジのリストのキーになる）
//	EdghListVector edges_;
//
//	//向きがあるグラフかどうか（有効グラフ）
//	bool bDigraph_;
//
//	//追加される次のノードのインデックス
//	int iNextNodeIndex_;
//public:
//	SparseGraph(bool digraph) :iNextNodeIndex_(0), bDigraph_(digraph) {};
//
//	//与えられたインデックスのノードを返す
//	const NodeType& GetNode(int idx)const 
//	{
//		if (0 > idx)
//		{
//			assert(!"SqareGraph0より下");
//		}
//		if (nodes_.size() <= idx)
//		{
//			assert(!"SqareGraph範囲外");
//		}
//		return nodes_[idx];
//	};
//
//	NodeType& GetNode(int idx)
//	{
//		if (0 > idx)
//		{
//			assert(!"SqareGraph0より下");
//		}
//		if (nodes_.size() <= idx)
//		{
//			assert(!"SqareGraph範囲外");
//		}
//		return nodes_[idx];
//	};
//
//	//エッジの参照を得る
//	const EdgeType& GetEdge(int from, int to)const;
//
//	EdgeType& GetEdge(int from, int to);
//
//	//次のフリーノードのインデックスを取得する。
//	int GetNextFreeNodeIndex()const { return m_iNextNodeIndex; };
//
//	//このグラフにノードを追加し、そのインデックスを取得する
//	int AddNode(NodeType node);
//
//	//インデックスをinvalid_node_indexに設定することでノードを削除する
//	void RemoveNode(int node);
//
//	//エッジを追加/削除するメソッド
//	void AddEdge(EdgeType edge);
//	void RemoveEdge(int from, int to);
//
//	//グラフ内のアクティブ/非アクティブなノードの個数を返す
//	int NumNodes()const { return nodes_.size() };
//
//	//グラフ内に存在するアクティブなノードの個数を返す
//	int NumActiveNodes()const;
//
//	//グラフ内の存在するエッジの個数を返す
//	int NumEdges()const;
//
//	//グラフ有向グラフの時trueを返す
//	bool isDigraph()const { return bDigraph_; };
//
//	//このグラフがノードを持ってない場合、trueを返す
//	bool isEmpty()const { return nodes_.empty(); };
//
//	//与えられたインデックスを持つノードがこのグラフに存在する場合、trueを返す
//	bool isPresent(int nd)const;
//
//	//オープンされたファイルストリームや、ファイル名からグラフを読み込んだり保存したりするメソッド
//	bool Save(const char* FileName)const;
//	bool Save(std::ofstream& stream)const;
//	bool Load(const char* FileName);
//	bool Load(std::ifstream& stream);
//
//	//新しいノードを挿入できるようにグラフをクリアする
//	void Clear();
//
//	//イテレータクライアントがノードやエッジにアクセスするのに用いる
//	class ConstEdgeIterator;
//	class EdgeIterator;
//	class NodeIterator;
//	class ConstNodeIterator;

};


