#include <iostream>

using namespace std;

template <class T>
class Node
{
private:
    T item;
    Node* left;
    Node* right;

public:
    Node();
    Node(T const&);
    T& getItem();
    Node<T>* getLeft();
    Node<T>* getRight();
    void setItem(T const&);
    void setLeft(Node*);
    void setRight(Node*);
};


template <class T>
Node<T>::Node()
{
    left = NULL;
    right = NULL;
}

template <class T>
Node<T>::Node(T const& it)
{
    item = it;
    left = NULL;
    right = NULL;
}

template <class T>
T& Node<T>::getItem()
{
    return item;
}

template <class T>
Node<T>* Node<T>::getLeft()
{
    return left;
}

template <class T>
Node<T>* Node<T>::getRight()
{
    return right;
}

template <class T>
void Node<T>::setItem(T const& it)
{
    item = it;
}

template <class T>
void Node<T>::setLeft(Node<T>* nd)
{
    left = nd;
}

template <class T>
void Node<T>::setRight(Node<T>* nd)
{
    right = nd;
}



template <class T>
class BST
{
private:
    Node<T>* head;
    int size;

public:
    BST();
    void add(T const&);
    Node<T>* find(T const& it);
};

template <class T>
BST<T>::BST()
{
    head = NULL;
    size = 0;
}

template <class T>
void BST<T>::add(T const& it)
{
    if(head == NULL)
    {
        head = new Node<T>(it);
    }
    else
    {
        Node<T>* prev = head;
        Node<T>* curr = (prev->getItem() < it)?prev->getLeft():prev->getRight();

        while(curr != NULL)
        {
            prev = curr;
            curr = (prev->getItem() < it)?prev->getLeft():prev->getRight();
        }

        if(prev->getItem() < it)
        {
            prev->setLeft(new Node<T>(it));
        }
        else
        {
            prev->setRight(new Node<T>(it));
        }
    }

    size++;
}

template <class T>
Node<T>* BST<T>::find(T const& it)
{
    Node<T>* curr = head;
    while(curr != NULL)
    {
        if(curr->getItem() == it)
        {
            break;
        }
        else
        {
            curr = (curr->getItem() < it)?curr->getLeft():curr->getRight();
        }
    }

    return curr;
}


int main()
{
    BST<int> tree = BST<int>();

    tree.add(5);
    tree.add(1);
    tree.add(7);
    tree.add(6);

    cout<<tree.find(5)->getItem()<<endl;
    return 0;
}