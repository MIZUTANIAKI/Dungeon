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

	//�m�[�h��ǉ�����
	int AddNode(NavGraphNode node);

	//�G�b�W��ǉ�����
	void AddEdge(GraphEdge edge);

	//�O���t���̃m�[�h����Ԃ�
	int NumNodes()const 
	{ 
		return static_cast<int>(nodes_.size());
	}

	//����͗L���O���t�ł��邩
	bool IsDigraph()const 
	{ 
		return bDigraph_; 
	}

	//�O���t���Ƀm�[�h�����݂��邩
	bool IsEmpty()const 
	{ 
		return nodes_.empty();
	}

	//Edge���擾����
	EdgeListVector GetEdges()const { return edges_; }

	//���̃t���[�m�[�h�̃C���f�b�N�X���擾����B
	int GetNextFreeNodeIndex()const { return iNextNodeIndex_; }

	//������
	void Clear()
	{
		nodes_.clear();
		edges_.clear();
		bDigraph_ = false;
		iNextNodeIndex_ = invalid_node_index;
	};

	//// �O���t�N���X������ list�z�� �� vector�z�� �ւ̃A�N�Z�X��e�Ղɂ���C�e���[�^�N���X
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
	//�O���t���\������m�[�h
	NodeVector nodes_;
	//�אڃG�b�W�̃x�N�^�[
	//�i�e�m�[�h�̃C���f�b�N�X�́A���̃m�[�h�Ɋ֘A�t����ꂽ�G�b�W�̃��X�g�̃L�[�ɂȂ�j
	EdgeListVector edges_;
	//�O���t�͗L���O���t�ł��邩�ǂ���
	bool bDigraph_;
	//���ɒǉ������m�[�h�̃C���f�b�N�X
	int iNextNodeIndex_;


//	//�O���t���\������m�[�h
//	NodeVector nodes_;
//
//	//�אڃG�b�W�̃x�N�^�[
//	//�i�e�m�[�h�̃C���f�b�N�X�́A���̃m�[�h�Ɋ֘A�t����ꂽ�G�b�W�̃��X�g�̃L�[�ɂȂ�j
//	EdghListVector edges_;
//
//	//����������O���t���ǂ����i�L���O���t�j
//	bool bDigraph_;
//
//	//�ǉ�����鎟�̃m�[�h�̃C���f�b�N�X
//	int iNextNodeIndex_;
//public:
//	SparseGraph(bool digraph) :iNextNodeIndex_(0), bDigraph_(digraph) {};
//
//	//�^����ꂽ�C���f�b�N�X�̃m�[�h��Ԃ�
//	const NodeType& GetNode(int idx)const 
//	{
//		if (0 > idx)
//		{
//			assert(!"SqareGraph0��艺");
//		}
//		if (nodes_.size() <= idx)
//		{
//			assert(!"SqareGraph�͈͊O");
//		}
//		return nodes_[idx];
//	};
//
//	NodeType& GetNode(int idx)
//	{
//		if (0 > idx)
//		{
//			assert(!"SqareGraph0��艺");
//		}
//		if (nodes_.size() <= idx)
//		{
//			assert(!"SqareGraph�͈͊O");
//		}
//		return nodes_[idx];
//	};
//
//	//�G�b�W�̎Q�Ƃ𓾂�
//	const EdgeType& GetEdge(int from, int to)const;
//
//	EdgeType& GetEdge(int from, int to);
//
//	//���̃t���[�m�[�h�̃C���f�b�N�X���擾����B
//	int GetNextFreeNodeIndex()const { return m_iNextNodeIndex; };
//
//	//���̃O���t�Ƀm�[�h��ǉ����A���̃C���f�b�N�X���擾����
//	int AddNode(NodeType node);
//
//	//�C���f�b�N�X��invalid_node_index�ɐݒ肷�邱�ƂŃm�[�h���폜����
//	void RemoveNode(int node);
//
//	//�G�b�W��ǉ�/�폜���郁�\�b�h
//	void AddEdge(EdgeType edge);
//	void RemoveEdge(int from, int to);
//
//	//�O���t���̃A�N�e�B�u/��A�N�e�B�u�ȃm�[�h�̌���Ԃ�
//	int NumNodes()const { return nodes_.size() };
//
//	//�O���t���ɑ��݂���A�N�e�B�u�ȃm�[�h�̌���Ԃ�
//	int NumActiveNodes()const;
//
//	//�O���t���̑��݂���G�b�W�̌���Ԃ�
//	int NumEdges()const;
//
//	//�O���t�L���O���t�̎�true��Ԃ�
//	bool isDigraph()const { return bDigraph_; };
//
//	//���̃O���t���m�[�h�������ĂȂ��ꍇ�Atrue��Ԃ�
//	bool isEmpty()const { return nodes_.empty(); };
//
//	//�^����ꂽ�C���f�b�N�X�����m�[�h�����̃O���t�ɑ��݂���ꍇ�Atrue��Ԃ�
//	bool isPresent(int nd)const;
//
//	//�I�[�v�����ꂽ�t�@�C���X�g���[����A�t�@�C��������O���t��ǂݍ��񂾂�ۑ������肷�郁�\�b�h
//	bool Save(const char* FileName)const;
//	bool Save(std::ofstream& stream)const;
//	bool Load(const char* FileName);
//	bool Load(std::ifstream& stream);
//
//	//�V�����m�[�h��}���ł���悤�ɃO���t���N���A����
//	void Clear();
//
//	//�C�e���[�^�N���C�A���g���m�[�h��G�b�W�ɃA�N�Z�X����̂ɗp����
//	class ConstEdgeIterator;
//	class EdgeIterator;
//	class NodeIterator;
//	class ConstNodeIterator;

};


