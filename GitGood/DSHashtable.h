#ifndef DSHASHTABLE_H
#define DSHASHTABLE_H

#include <functional>
#include <iostream>

#include "AVLTree.h"

using namespace std;

/*
888    888                   888
888    888                   888
888    888                   888
8888888888  8888b.  .d8888b  88888b.
888    888     "88b 88K      888 "88b
888    888 .d888888 "Y8888b. 888  888
888    888 888  888      X88 888  888
888    888 "Y888888  88888P' 888  888



888b    888               888
8888b   888               888
88888b  888               888
888Y88b 888  .d88b.   .d88888  .d88b.
888 Y88b888 d88""88b d88" 888 d8P  Y8b
888  Y88888 888  888 888  888 88888888
888   Y8888 Y88..88P Y88b 888 Y8b.
888    Y888  "Y88P"   "Y88888  "Y8888
*/

template<class K, class V>
class HashNode
{
public:
    K key;
    V value;
    bool operator== (const HashNode<K, V>&) const;
    bool operator> (const HashNode<K, V>&) const;
    bool operator< (const HashNode<K, V>&) const;
};

template<class K, class V>
bool HashNode<K, V>::operator== (const HashNode<K, V>& rhs) const
{
    return (key == rhs.key);
}

template<class K, class V>
bool HashNode<K, V>::operator> (const HashNode<K, V>& rhs) const
{
    return (key > rhs.key);
}

template<class K, class V>
bool HashNode<K, V>::operator< (const HashNode<K, V>& rhs) const
{
    return (key < rhs.key);
}

/*
888    888                   888
888    888                   888
888    888                   888
8888888888  8888b.  .d8888b  88888b.
888    888     "88b 88K      888 "88b
888    888 .d888888 "Y8888b. 888  888
888    888 888  888      X88 888  888
888    888 "Y888888  88888P' 888  888



88888888888       888      888
    888           888      888
    888           888      888
    888   8888b.  88888b.  888  .d88b.
    888      "88b 888 "88b 888 d8P  Y8b
    888  .d888888 888  888 888 88888888
    888  888  888 888 d88P 888 Y8b.
    888  "Y888888 88888P"  888  "Y8888
*/

template<class K, class V>
class HashTable
{
public:
    HashTable();
    HashTable(const int);
    HashTable(const HashTable<K, V>&);

    HashTable& operator= (const HashTable<K, V>&);

    bool operator== (const HashTable<K, V>&) const;

    V& operator[] (const K);

    bool isEmpty();

    ~HashTable();

private:
    AvlTree<HashNode<K, V>>* table;
    int size;
    int hash(K);
    //int hash(String);
};

template<class K, class V>
HashTable<K, V>::HashTable()
{
    size = 10;
    table = new AvlTree<HashNode<K, V>>[size];
}

template<class K, class V>
HashTable<K, V>::HashTable(const int sizeNew)
{
    size = sizeNew;
    table = new AvlTree<HashNode<K, V>>[size];
}

template<class K, class V>
HashTable<K, V>::HashTable(const HashTable<K, V>& rhs)
{
    size = rhs.size;
    table = new AvlTree<HashNode<K, V>>[size];
    for (int i = 0; i < size; i++)
    {
        table[i] = rhs.table[i];
    }
}

template<class K, class V>
HashTable<K, V>& HashTable<K, V>::operator= (const HashTable<K, V>& rhs)
{
    if (this->table != nullptr)
    {
        delete[] table;
    }

    size = rhs.size;
    table = new AvlTree<HashNode<K, V>>[size];
    for (int i = 0; i < size; i++)
    {
        table[i] = rhs.table[i];
    }
    return *this;
}

template<class K, class V>
bool HashTable<K, V>::isEmpty()
{
    for (int i = 0; i < size; i++)
    {
        if (!table[i].isEmpty())
        {
            return false;
        }
    }
    return true;
}

template<class K, class V>
bool HashTable<K, V>::operator== (const HashTable<K, V>& rhs) const
{
    if (size != rhs.size)
    {
        return false;
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            if (table[i] != rhs.table[i])
            {
                return false;
            }
        }
    }
    return true;
}

template<class K, class V>
V& HashTable<K, V>::operator[] (const K key)
{
    int temp = hash(key);
    HashNode<K, V> tempNode;
    tempNode.key = key;
    if (table[temp].contains(tempNode))
    {
        return table[temp].find(tempNode).value;
    }
    else
    {
        table[temp].insert(tempNode);
        return table[temp].find(tempNode).value;
    }
}

template<class K, class V>
HashTable<K, V>::~HashTable()
{
    delete[] table;
}

template<class K, class V>
int HashTable<K, V>::hash(K key)
{
    return (std::hash<K>()(key) % size);
}

//template<class K, class V>
//int HashTable<K, V>::hash(String key)
//{
//    return (std::hash<String>()(key.c_str()) % size);
//}

#endif // DSHASHTABLE_H
