#pragma once

template<typename Chemu, typename Chto> class TreeDict 
{
public:
    TreeDict()
    {
        size_t size = 0;
        Node* m_root = nullptr;
    }
	void add(Chemu che, Chto cht);
	Chto& operator[](Chemu che);
    size_t getSize()const
    {
        return size;
    }; size_t getHeight()const
    {
        int a = 0, b = 0;
        Node* tmp = m_root;
        if (tmp->left != nullptr)
            a = getHeightR(tmp->left);
        if (tmp->right != nullptr)
            b = getHeightR(tmp->right);
        if (a > b)
            return a++;
        else
            return b++;
    }
private:
    struct Para
    {
        Chemu che;
        Chto cht;
    };
    struct Node
    {
        Node* left, * right, * prev;
        Para data;
    };
    size_t size;
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
};

    














template<typename Chemu, typename Chto> Chto& TreeDict<Chemu, Chto>::operator[](Chemu che)
{
    if (!m_root)
    {
        Node* tmp = new Node;
        tmp->left = tmp->right = tmp->prev = nullptr;
        Para p;
        p.che = che;
        tmp->data = p;
        m_root = tmp;
        return m_root->data.cht;
    }
    Node* cur = m_root;
    Node** next = nullptr;
    while (cur != nullptr)
    {
        if (cur->data.che == che)
            return cur->data.cht;

        if (che < cur->data.che)
            next = &cur->left;
        else if (che > cur->data.che)
            next = &cur->right;

        if (*next == nullptr)
        {
            Node* tmp = new Node;
            tmp->prev = cur;
            tmp->left = tmp->right = nullptr;
            Para p;
            p.che = che;
            tmp->data = p;

            *next = tmp;
            return (*next)->data.cht;
        }

        cur = *next;

    }
}

template<typename Chemu, typename Chto> void TreeDict<Chemu, Chto>::add(Chemu che, Chto cht)
{
    if (!m_root)
    {
        Node* tmp = new Node;
        tmp->left = tmp->right = tmp->prev = nullptr;
        Para p;
        p.che = che;
        p.cht = cht;
        tmp->data = p;
        m_root = tmp;
    }
    Node* cur = m_root;
    Node** next = nullptr;
    while (cur != nullptr)
    {
        if (cur->data.che == che)
            return;

        if (che < cur->data.che)
            next = &cur->left;
        else if (che > cur->data.che)
            next = &cur->right;

        if (*next == nullptr)
        {
            Node* tmp = new Node;
            tmp->left = tmp->right = nullptr;
            tmp->prev = cur;
            Para p;
            p.che = che;
            p.cht = cht;
            tmp->data = p;
            *next = tmp;
            return;
        }

        cur = *next;
    }

}
