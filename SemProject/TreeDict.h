#pragma once

template<typename Chemu, typename Chto> class TreeDict {
public:
	TreeDict();
	void add(Chemu che, Chto cht);
	Chto& operator[](Chemu che);
	size_t getSize()const;
private:
    struct Para
    {
        Chemu che;
        Chto cht;
    };
    struct Node
    {
        Node* left, * right;
        Para data;
    };
    size_t size;
    Node* m_root;

};

template<typename Chemu, typename Chto> Chto& TreeDict<Chemu, Chto>::operator[](Chemu che)
{
    Node* cur = m_root;
    while (cur != nullptr)
    {
        if (cur->data.che == che)
            return cur->data.cht;
        else if (che < cur->data.che)
        {
            if (cur->left == nullptr)
            {
                Node* tmp = new Node;
                tmp->left = tmp->right = nullptr;
                Para p;
                tmp->data = p;
                cur->left = tmp;
            }
            cur = cur->left;
        }   
        else if (che > cur->data.che)
        {
            if (cur->right == nullptr)
            {
                Node* tmp = new Node;
                tmp->left = tmp->right = nullptr;
                Para p;
                tmp->data = p;
                cur->right = tmp;
            }
            cur = cur->right;
        }
    }
}