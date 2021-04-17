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

        if (tmp)
            while (tmp->left != nullptr)
            {
                tmp = tmp->left;
            };
       
        m.mark = tmp;

        return m;
    };
    Marker afterEnd()
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
    bool removeElementByKey(Key key);
};


template<typename Key, typename Value> bool TreeDict<Key, Value>::removeElementByKey(Key key)
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
            Node** tmp;
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
            
            
            if (ptr->prev)
            {
                if (key < ptr->prev->data.key)
                    tmp = &(ptr->prev->left);
                else
                    tmp = &(ptr->prev->right);

                (*tmp) = newNode;
            }


            delete ptr;
            size--;


            //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ Балансировка/////////////////////////////\\

            if (size == 0)
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
    tmp->left = tmp->right  = nullptr;
    tmp->data.key = key;
    size++;

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
    }
}
template<typename Key, typename Value> void TreeDict<Key, Value>::DoRotate(Node* current)
{
    Node* tmp = current;
    
    if (getHeight(current->left) > getHeight(current->right))
    {
        if (getHeight(current->left->left) > getHeight(current->left->right))
        {
            
            Node* tmpLeft = current->left;
            current->left = current->left->left;
            current->left->prev = current;
            current->left->left = tmpLeft;
            current->left->prev = current->left;
            current->left->left->left = nullptr;
        }
        else
        {
           
            current->left = current->left->right;
            current->left->prev->right = nullptr;
            current->left->left = current->left->prev;
            current->left->left->prev = current->left;
            current->left->prev = current;
            Node* tmpLeft = current->left;
            current->left = current->left->left;
            current->left->prev = current;
            current->left->left = tmpLeft;
            current->left->left->prev = current->left;
            current->left->left->left = nullptr;
        }
    }
    else
    {
        if (getHeight(current->right->right) > getHeight(current->right->left))
        {
            Node* tmpRight = current->right;
            current->right = current->right->right;
            current->right->prev = current;
            current->right->right = tmpRight;
            current->right->prev = current->right;
            current->right->right->right = nullptr;
        }
        else 
        {
           
            current->right = current->right->left;
            current->right->prev->left = nullptr;
            current->right->right = current->right->prev;
            current->right->right->prev = current->right;
            current->right->prev = current;
            Node* tmpRight = current->right;
            current->right = current->right->right;
            current->right->prev = current;
            current->right->right = tmpRight;
            current->right->right->prev = current->right;
            current->right->right->right = nullptr;
        }
    }
}
template<typename Key, typename Value> void TreeDict<Key, Value>::add(Key key, Value value)
{
    size++;
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
