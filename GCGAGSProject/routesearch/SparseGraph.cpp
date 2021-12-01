#include "SparseGraph.h"

int SparseGraph::AddNode(NavGraphNode node)
{
	//�m�[�h���T�C�Y���傫�����ǂ���
	if (node.Index() < static_cast<int>(nodes_.size()))
	{
		//�������ꍇ�A���̂܂ܒT���B���̃m�[�h�̃C���f�b�N�X�𑗂�

		//assert(nodes_[node.Index()].Index() == invalid_node_index && "SparseGraph�N���X[AddNode]");
		nodes_[node.Index()] = node;
		return iNextNodeIndex_;
	}
	else
	{
		//�傫���ꍇ�A�ǉ�����A���̃m�[�h�̃C���f�b�N�X�𑗂�
		//assert(node.Index() == iNextNodeIndex_ && "SparseGraph�N���X[AddNode]");
		nodes_.push_back(node);
		edges_.push_back(EdgeList());
		return iNextNodeIndex_++;
	}
}

void SparseGraph::AddEdge(GraphEdge edge)
{
	//�l���A���ݒ肾�����炱���ŏI������
	if ((nodes_[edge.To()].Index() == invalid_node_index) || (nodes_[edge.From()].Index() == invalid_node_index))
	{
		return;
	}
	bool itrCheck = false;
	//�����O�m�[�h�ŁA�����s�悪���邩
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
		//�L���O���t�̏ꍇ�����ŏI��
		return;
	}

	//�����s��m�[�h�ŁA�����O�m�[�h�����邩
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

	// �V�����G�b�W���쐬�i���̃G�b�W�͏�L��push_back�����G�b�W�Ƒ΂ɂȂ�G�b�W�ł���j
	GraphEdge NewEdge = edge;
	NewEdge.SetTo(edge.From());
	NewEdge.SetFrom(edge.To());
	edges_[edge.To()].push_back(NewEdge);
}

