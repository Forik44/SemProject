#pragma once
#include <math.h>

template<typename Key, typename Value> class TreeDict
{
private:
    friend class Marker;
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
             return a++;
         else
             return b++;
     }
     bool checkRotate(Node* current);
     void leadRotate(Node* current);
     void DoRotate(Node* current);
    
public:
    TreeDict()
    {
        size = 0;
        m_root = nullptr;
    }
    
    void add(Key key, Value val);
    Value& operator[](Key key);

    class Marker
    {
    private:
        Node* mark;
        Node* getNextNode();
    public:
        friend class UniDict;
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
        bool operator==(const Marker& secondMarker) const
        {
            return mark == secondMarker.mark;
        };
        bool operator!=(const Marker& secondMarker) const
        {
            return mark != secondMarker.mark;
        }
        bool canMoveNext()
        {
            return getNextNode() != nullptr;
        };
    };
    Marker init()
    {
        Marker m;
        Node* tmp = m_root;
        while (tmp->left != nullptr)
        {
            tmp = tmp->left;
        }
        m.setMarkerSize(size);
        m.mark = tmp;
 
        return m;
    };
    Marker& afterEnd()
    {
        Marker m;
        m.mark = nullptr;
        return m;
    };
    size_t getSize()const
    {
        return size;
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

template<typename Key, typename Value> bool TreeDict<Key, Value>::checkRotate(Node* current)
{
    return fabs(getHeight(current->left) - getHeight(current->right)) < 2;
}

template<typename Key, typename Value> void TreeDict<Key, Value>::leadRotate(Node* current)
{
    while (current != m_root)
    {
 
        if (checkRotate(current) < 2)
            current = current->prev;
        else
        {
            DoRotate(current);
            current = current->prev->prev;
        }
    }
}
template<typename Key, typename Value> void TreeDict<Key, Value>::DoRotate(Node* current)
{
    Node* tmp = current;
    
    if (getHeight(current->left) > getHeight(current->right))
    {
        if (getHeight(current->left->left) > getHeight(current->left->right))
        {
            
            current->prev->left = current->left;
            tmp->left->prev = tmp->prev;
            tmp->left->right = tmp;
            tmp->prev = tmp->left;
            tmp->left = nullptr;
        }
        else
        {
            Node* tmpLeft = current->left;
            current->left = current->left->right;
            tmpLeft->right->prev = tmpLeft->prev;
            tmpLeft->right->left = tmpLeft;
            tmpLeft->prev = tmpLeft->right;
            current->prev->left = current->left;
            tmp->left->prev = tmp->prev;
            tmp->left->right = tmp;
            tmp->prev = tmp->left;
            tmp->left = nullptr;
        }
    }
    else
    {
        if (getHeight(current->right->right) > getHeight(current->right->left))
        {
            current->prev->right = current->right;
            tmp->right->prev = tmp->prev;
            tmp->right->left = tmp;
            tmp->prev = tmp->right;
            tmp->left = nullptr;
        }
        else 
        {
            Node* tmpRight = current->right;
            current->right = current->right->left;
            tmpRight->left->prev = tmpRight->prev;
            tmpRight->left->right = tmpRight;
            tmpRight->prev = tmpRight->left;
            current->prev->right = current->right;
            tmp->right->prev = tmp->prev;
            tmp->right->left = tmp;
            tmp->prev = tmp->right;
            tmp->left = nullptr;
        }
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

        if (key > cur->data.key)
            next = &cur->right;
        else if (key < cur->data.key)
            next = &cur->left;

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
            leadRotate(tmp);
            return;
        }
        cur = *next;
        
    }

}
