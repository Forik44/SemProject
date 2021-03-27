#pragma once

template<typename Chemu, typename Chto> class TreeDict {
public:
	TreeDict();
	void add(Chemu che, Chto cht);
	Chto& operator[](Chemu cht);
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

template<typename Chemu, typename Chto> Chto& TreeDict::operator[](Chemu che)
{
    Node* cur = m_root;
    while (cur != nullptr)
    {
        if (cur->data.che == che)
            return cur->data.cht;
        
        else if (che < cur->data.che)
            cur = cur->left;
        else if (che > cur->data.che)
            cur = cur->right;

    }
}