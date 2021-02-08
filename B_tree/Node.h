#pragma once

#include <vector>

template<class T>
class Node
{
public:
	Node(T data = T(), Node<T>* parent = nullptr, std::vector<T> _childs = {0})
	{
		hash_Node = operator();
		this->parent = parent;
		this->_childs = _childs;
	}

	~Node() { parent = nullptr; }

	size_t operator()() const noexcept
	{
		std::size_t h1 = std::hash<std::string>{} (this->data);
		std::size_t h2 = std::hash<std::string>{} (this->_childs);

		return h1 ^ (h2 << 1);
	}
	const size_t GetHash() const { return hash_Node; }

	Node<T>* parent;
	T data;
	std::vector<T> _childs;
private:
	size_t hash_Node;
};
