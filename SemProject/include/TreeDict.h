#pragma once
#include <math.h>

template<typename Key, typename Value> class TreeDict
{
private:
	friend class iterator;
	struct Para
	{
		Key key;
		Value value;
	};
	struct Node
	{
		Node* left, * right, * prev;
		Para data;
	};
	size_t _size;
	Node* m_root;
	size_t getHeightR(Node* tmp)const
	{
		int a = 0, b = 0;
		if (tmp->left != nullptr)
		{
			a = getHeightR(tmp->left);
			a++;
		}
		if (tmp->right != nullptr)
		{
			b = getHeightR(tmp->right);
			b++;
		}
		if (a == 0 && b == 0)
			return 1;
		if (a > b)
			return a;
		else
			return b;

	}
	size_t getHeight(Node* current)const
	{
		int a = 0, b = 0;
		Node* tmp = current;
		if (tmp != nullptr) {
			if (tmp->left != nullptr || tmp->right != nullptr)
			{
				if (tmp->left != nullptr)
					a = getHeightR(tmp->left);
				if (tmp->right != nullptr)
					b = getHeightR(tmp->right);
			}
			else return 1;
		}
		else return 0;
		if (a > b)
			return a + 1;
		else
			return b + 1;
	}
	bool checkRotate(Node* current);
	void leadRotate(Node* current);
	void DoRotate(Node* current);
	void DoRotateRoot(Node* current);
public:
	Node* copyBranch(Node* original, Node* prev)
	{
		if (!original)
			return nullptr;

		Node* newNode = new Node;
		newNode->data = original->data;
		newNode->prev = prev;
		newNode->right = copyBranch(original->right, newNode);
		newNode->left = copyBranch(original->left, newNode);

		return newNode;
	}
	void removeBranch(Node* node)
	{
		if (!node)
			return;
		removeBranch(node->left);
		removeBranch(node->right);
		delete node;
	};
	TreeDict()
	{
		_size = 0;
		m_root = nullptr;
	}
	~TreeDict()
	{
		removeBranch(m_root);
	}
	TreeDict(const TreeDict& original)
	{
		_size = original._size;
		m_root = copyBranch(original.m_root, nullptr);
	}
	TreeDict& operator= (const TreeDict& original)
	{
		_size = original._size;
		m_root = copyBranch(original.m_root, nullptr);
		return *this;
	}
	Value& operator[](Key key);
	void add(Key key, Value val);
	class iterator
	{
	private:
		Node* mark;
		Node* getNextNode()
		{
			Node* tmp = this->mark;
			if (tmp->right != nullptr)
			{
				tmp = tmp->right;
				while (tmp->left != nullptr)
				{
					tmp = tmp->left;
				}
				return tmp;
			}
			else
			{
				while (tmp->prev != nullptr)
				{
					if (tmp == tmp->prev->right)
					{
						tmp = tmp->prev;
					}
					else
					{
						tmp = tmp->prev;
						return tmp;
					}
				}
				return nullptr;
			}
		}
	public:
		friend class TreeDict;
		Para& operator*()
		{
			return (*mark).data;
		};
		const Para& operator*() const
		{
			return (*mark).data;
		};
		void operator++()
		{
			mark = getNextNode();
		};
		void operator++(int)
		{
			mark = getNextNode();
		};
		bool operator==(const iterator& secondMarker) const
		{
			return mark == secondMarker.mark;
		};
		bool operator!=(const iterator& secondMarker) const
		{
			return mark != secondMarker.mark;
		}
		bool canMoveNext()
		{
			return getNextNode() != nullptr;
		};
	};
	iterator begin()
	{
		iterator m;
		Node* tmp = m_root;

		if (tmp)
			while (tmp->left != nullptr)
			{
				tmp = tmp->left;
			};

		m.mark = tmp;

		return m;
	};
	iterator end()
	{
		iterator m;
		m.mark = nullptr;
		return m;
	};
	size_t size()const
	{
		return _size;
	};
	size_t getHeight()const
	{
		int a = 0, b = 0;
		Node* tmp = m_root;
		if (tmp != nullptr) {
			if (tmp->left != nullptr || tmp->right != nullptr)
			{
				if (tmp->left != nullptr)
					a = getHeightR(tmp->left);
				if (tmp->right != nullptr)
					b = getHeightR(tmp->right);
			}
			else return 1;
		}
		else return 0;

		if (a > b)
			return a++;
		else
			return b++;
	}
	bool erase(Key key);
};


template<typename Key, typename Value> bool TreeDict<Key, Value>::erase(Key key)
{
	Node* ptr = m_root;
	while (ptr)
	{
		if (key > ptr->data.key)
			ptr = ptr->right;
		else if (key < ptr->data.key)
			ptr = ptr->left;
		else
		{
			Node** tmp = nullptr;
			Node* newNode;

			if (ptr->right)
			{
				for (newNode = ptr->right; newNode->left; newNode = newNode->left);

				if (newNode->prev == ptr)
					tmp = &(ptr->right);
				else
					tmp = &(newNode->prev->left);

				(*tmp) = newNode->right;
				if (newNode->right)
				{
					tmp = &(newNode->right->prev);
					(*tmp) = newNode->prev;
				}


				tmp = &(newNode->right);
				(*tmp) = ptr->right;
				if (ptr->right)
				{
					tmp = &(ptr->right->prev);
					(*tmp) = newNode;
				}


				tmp = &(newNode->left);
				(*tmp) = ptr->left;
				if (ptr->left)
				{
					tmp = &(ptr->left->prev);
					(*tmp) = newNode;
				}


				tmp = &(newNode->prev);
				(*tmp) = ptr->prev;
			}
			else if (ptr->left)
			{
				newNode = ptr->left;
				tmp = &(newNode->prev);
				(*tmp) = ptr->prev;
			}
			else
			{
				newNode = nullptr;
			}

			leadRotate(ptr);
			if (ptr->prev)
			{
				if (key < ptr->prev->data.key)
					tmp = &(ptr->prev->left);
				else
					tmp = &(ptr->prev->right);

				(*tmp) = newNode;
			}


			delete ptr;
			_size--;
			
			//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ Балансировка/////////////////////////////\\
            

			if (_size == 0)
				m_root = nullptr;

			return true;

		}

	}

	return false;
}
template<typename Key, typename Value> Value& TreeDict<Key, Value>::operator[](Key key)
{
	Node** next = nullptr;
	Node* cur = m_root;

	for (; cur; cur = *next)
	{
		if (key < cur->data.key)
			next = &cur->left;
		else if (key > cur->data.key)
			next = &cur->right;
		else
			return cur->data.value;

		if (*next == nullptr)
			break;
	}

	Node* tmp = new Node;
	tmp->left = tmp->right = nullptr;
	tmp->data.key = key;
	_size++;

	if (!m_root)
	{
		tmp->prev = nullptr;
		m_root = tmp;
	}
	else
	{
		tmp->prev = cur;
		*next = tmp;
	}

	return tmp->data.value;
}
template<typename Key, typename Value> bool TreeDict<Key, Value>::checkRotate(Node* current)
{
	int a = getHeight(current->left);
	int b = getHeight(current->right);
	int c;
	if (a - b < 0)
		c = -a + b;
	else
		c = a - b;
	return c < 2;
}
template<typename Key, typename Value> void TreeDict<Key, Value>::leadRotate(Node* current)
{
	while (current != m_root)
	{
		if (checkRotate(current))
			current = current->prev;
		else
		{
			DoRotate(current);
			current = current->prev->prev;
		}
		   if (current == m_root)
		   {
			   if (!checkRotate(current))
			   {
				   DoRotateRoot(current);
				   m_root = current->prev;
				   current = current->prev;
			   }
		   }
	}
}
template<typename Key, typename Value> void TreeDict<Key, Value>::DoRotateRoot(Node* current)
{
	if (getHeight(current->right) > getHeight(current->left))
	{
		Node* tmpRight = nullptr;
		tmpRight = current->right->left;
		current->right->left = current;
		current->prev = current->right;
		current->prev->prev = nullptr;
		current->right = tmpRight;
		if (tmpRight != nullptr)
			tmpRight->prev = current;
	}
	else
	{
		Node* tmpLeft = current->left->right;
		current->left->right = current;
		current->prev = current->left;
		current->prev->prev = nullptr;
		current->left = tmpLeft;
		if (tmpLeft != nullptr)
			tmpLeft->prev = current;

	}
}
template<typename Key, typename Value> void TreeDict<Key, Value>::DoRotate(Node* current)
{
	if (getHeight(current->left) > getHeight(current->right))
	{
		Node* tmpRight = current->left->right;
		if (current->prev->left == current)
		{
			current->prev->left = current->left;
			current->left->right = current;
			current->left->prev = current->prev;
			current->prev = current->left;
			current->left = tmpRight;
			if (tmpRight != nullptr)
				tmpRight->prev = current;
		}
		else
		{
			current->prev->right = current->left;
			current->left->right = current;
			current->left->prev = current->prev;
			current->prev = current->left;
			current->left = tmpRight;
			if (tmpRight != nullptr)
				tmpRight->prev = current;
		}
	}
	else
	{
		Node* tmpLeft = current->right->left;
		if (current->prev->right == current)
		{
			current->prev->right = current->right;
			current->right->left = current;
			current->right->prev = current->prev;
			current->prev = current->right;
			current->right = tmpLeft;
			if (tmpLeft != nullptr)
				tmpLeft->prev = current;

		}
		else
		{
			current->prev->left = current->right;
			current->right->left = current;
			current->right->prev = current->prev;
			current->prev = current->right;
			current->right = tmpLeft;
			if (tmpLeft != nullptr)
				tmpLeft->prev = current;
		}

	}
}
template<typename Key, typename Value> void TreeDict<Key, Value>::add(Key key, Value value)
{
	_size++;
	Node* tmp = new Node;
	tmp->left = tmp->right = nullptr;
	tmp->data.key = key;
	tmp->data.value = value;

	if (!m_root)
	{
		tmp->prev = nullptr;
		m_root = tmp;
		return;
	}


	Node** next = nullptr;

	for (Node* cur = m_root; cur; cur = *next)
	{
		if (key > cur->data.key)
			next = &cur->right;
		else if (key < cur->data.key)
			next = &cur->left;
		else
			return;

		if (*next == nullptr)
		{
			tmp->prev = cur;
			*next = tmp;
			leadRotate(tmp);
			return;
		}
	}

}
