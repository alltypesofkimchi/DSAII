//Do Yun Jason Kim
//DSA II, program 2
//heap.cpp

#include <iostream>
#include "heap.h"

using namespace std;

heap::heap(int capacity)
//constructor
{
    this->capacity = capacity;
    this->filled = 0;
    data.resize(capacity+1);
    mapping = new hashTable(capacity*2);
}

//Define Insert function
int heap::insert(const std::string &id, int key, void *pv)
{
    if(filled == capacity)
        return 1;
    else if(filled < capacity && mapping->contains(id))
        return 2;
    else
    {
        if (filled == capacity - 1)
            data.resize(capacity*2);
        filled++;
        //insert the node into the heap
        data[filled].id = id;
        data[filled].key = key;
        data[filled].pData = pv;
        //insert the id and pointer into the hashtable
        mapping->insert(id, &data[filled]);
        percUp(filled);
        return 0;
    }
}

//Define setKey function
int heap::setKey(const std::string &id, int key)
{
    bool havekey = false;
    node *pn = static_cast<node *> (mapping->getPointer(id, &havekey));
    int nodePos = getPos(pn);

    if(!havekey)
        return 1;
    data[nodePos].key = key;
    //perform percolate if heap order property is violated
    bool perc;
    perc = ((nodePos*2 <= filled) && (data[nodePos].key > data[nodePos*2].key)) || \
            ((nodePos*2+1 <= filled) && (data[nodePos].key > data[nodePos*2+1].key))|| \
            (nodePos == 1);
    if(perc)
        percDown(nodePos);
    else if(data[nodePos].key < data[nodePos/2].key)
        percUp(nodePos);
    return 0;
}

//Define deleteMin function
int heap::deleteMin(std::string *pId, int *pKey, void *ppData)
{
    if(filled == 0)
        return 1;
    //Optional pointers
    if(pId)
        *pId = data[1].id;
    if(pKey)
        *pKey = data[1].key;
    if(ppData)
        *(static_cast<void **> (ppData)) = data[1].pData;
    //remove existing string from hashtable
    mapping->remove(data[1].id);
    //overwrite and percolate
    data[1] = data[filled];
    filled--;
    percDown(1);
    return 0;
}

//Define remove function
int heap::remove(const std::string &id, int *pKey, void *ppData)
{
    bool havekey = false;
    node *pn = static_cast<node *> (mapping->getPointer(id, &havekey));
    int nodePos = getPos(pn);

    if(!havekey)
        return 1;
    //Optional pointers
    if(pKey)
        *pKey = data[nodePos].key;
    if(ppData)
        ppData = data[nodePos].pData;
    //remove old id from hashtable, overwrite with last element and set new pointer
    mapping->remove(id);
    data[nodePos] = data[filled];
    mapping->setPointer(data[nodePos].id, &data[nodePos]);
    filled--;
    //perform percolate if needed
    bool perc;
    perc = ((nodePos*2 <= filled) && (data[nodePos].key > data[nodePos*2].key))|| \
            ((nodePos*2+1 <= filled) && (data[nodePos].key > data[nodePos*2+1].key))|| \
            (nodePos==1);
        if(perc)
            percDown(nodePos);
        else if(data[nodePos].key < data[nodePos/2].key)
            percUp(nodePos);
        return 0;
}

//Define percolateUp
void heap:: percUp(int posCur)
{
    int space;
    space = posCur;
    node tmp = data[posCur];
    for( ; space > 1 && tmp.key < data[space/2].key; space /= 2)
    {
        data[space] = data[space/2];
        mapping->setPointer(data[space].id, &data[space]);
    }
    data[space] = tmp;
    mapping->setPointer(data[space].id, &data[space]);
}

//Define percolateDown
void heap::percDown(int posCur)
{
    int space;
    space = posCur;
    int child;
    node tmp = data[posCur];
    for( ; space*2 <= filled; space = child)
    {
        child = space*2;
        if(child != filled && data[child+1].key < data[child].key)
            child++;
        if(data[child].key < tmp.key)
        {
            data[space] = data[child];
            mapping->setPointer(data[space].id, &data[space]);
        }
        else
            break;
    }
    data[space] = tmp;
    mapping->setPointer(data[space].id, &data[space]);
}

//Define getPos function
int heap::getPos(node *pn)
{
    int pos;
    pos = pn - &data[0];
    return pos;
}
