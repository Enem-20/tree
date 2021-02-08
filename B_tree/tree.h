#pragma once

#include <unordered_map>
#include <stack>

#include "Node.h"

template<class T>
class tree
{
private:
	B_tree(const B_tree&) = delete;
	void operator=(const B_tree&) = delete;
	
public:
	const Node<T>* emplace(Node<T>* newNode, Node<T>* previousNode = nullptr)
	{
		if (!newNode && !previousNode ) { return nullptr; }
		if (!m_head) { return m_head = newNode; }

		previousNode->_childs.push_back(newNode);
		newNode->parent = previousNode;
		return newNode;
	}
	const Node<T>* emplace(Node<T>* newNode, std::size_t hashPreviousNode = 0)
	{
		if (!newNode && !hashPreviousNode) { return nullptr; }
		if (!m_head) { return m_head = newNode; }

		return (m_fastGetter.find(hashPreviousNode))
			? m_fastGetter.find(hashPreviousNode)->_childs.push_back(newNode), newNode
			: nullptr;
	}
	const Node<T>* emplace(T data, Node<T>* previousNode = nullptr)
	{
		if (!m_head) { return m_head = new Node<T>(data); }
		return previousNode->_childs.push_back(new Node<T>(data));
	}

	Node<T>* GetHead() const
	{
		return m_head;
	}
	bool erase(Node<T>* _node) //Erase node with connect _childs to previous
	{
		if (!_node) { return false; }
		Node<T>* current = m_head;
		std::vector<Node<T>*> vec;
		std::stack<Node<T>*> st;
		st.push(current);

		while (!st.empty())
		{
			for (auto it : st.top()->_childs)
			{
				if (_node == it)
				{
					std::copy(it->_childs.begin(), it->_childs.end(), vec);
					for (auto it2 : vec)
					{
						it2.parent = st.top();
					}
					st.top()->erase(it);
					st.top()->_childs.push_back(vec);					

					return true;
				}
				st.push(it);
			}
			st.pop();
		}

	}
	bool fastErase(std::size_t hashPreviousNode, Node<T>* _node)
	{
		auto itPrevNode = m_fastGetter.find(hashPreviousNode);
		std::stack<Node<T>*> st;
		st.push(itPrevNode);

		if(itPrevNode == m_fastGetter.end())
		{return false;}

		for (auto it : itPrevNode->_childs)
		{
			if (it == _node)
			{
				st.top()->erase(it);

				return true;
			}
		}
	}
	bool fastErase(Node<T>* PreviousNode, Node<T>* _node)
	{

	}
private:
	Node<T>* m_head;
	std::unordered_map<size_t, Node<T>*> m_fastGetter;
};