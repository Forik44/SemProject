#pragma once

template<typename Key, typename Value> class TreeDict
{
private:
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
public:
    TreeDict()
    {
        size = 0;
        m_root = nullptr;
    }
    void add(Key key, Value val);
    Value& operator[](Key key);
    size_t getSize()const
    {
        return size;
    };
    size_t getHeight()const
    {
        int a = 0, b = 0;
        Node* tmp = m_root;
        if (tmp != nullptr) {
            if (tmp->left != nullptr && tmp->right != nullptr)
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
};

template<typename Key, typename Value> Value& TreeDict<Key, Value>::operator[](Key key)
{
    if (!m_root)
    {
        Node* tmp = new Node;
        tmp->left = tmp->right = tmp->prev = nullptr;
        Para p;
        p.key = key;
        tmp->data = p;
        m_root = tmp;

        return m_root->data.value;
    }

    Node* cur = m_root;
    Node** next = nullptr;

    while (cur != nullptr)
    {
        if (cur->data.key == key)
            return cur->data.value;

        if (key < cur->data.key)
            next = &cur->left;
        else if (key > cur->data.key)
            next = &cur->right;

        if (*next == nullptr)
        {
            Node* tmp = new Node;
            tmp->prev = cur;
            tmp->left = tmp->right = nullptr;
            Para p;
            p.key = key;
            tmp->data = p;

            *next = tmp;
            return (*next)->data.value;
        }

        cur = *next;
    }
}

template<typename Key, typename Value> void TreeDict<Key, Value>::add(Key key, Value value)
{
    size++;
    if (!m_root)
    {
        Node* tmp = new Node;
        tmp->left = tmp->right = tmp->prev = nullptr;
        Para p;
        p.key = key;
        p.value = value;
        tmp->data = p;
        m_root = tmp;

        return;
    }

    Node* cur = m_root;
    Node** next = nullptr;

    while (cur != nullptr)
    {
        if (cur->data.key == key)
            return;

        if (key < cur->data.key)
            next = &cur->left;
        else if (key > cur->data.key)
            next = &cur->right;

        if (*next == nullptr)
        {
            Node* tmp = new Node;
            tmp->left = tmp->right = nullptr;
            tmp->prev = cur;
            Para p;
            p.key = key;
            p.value = value;
            tmp->data = p;
            *next = tmp;
            return;
        }

        cur = *next;
    }

}
