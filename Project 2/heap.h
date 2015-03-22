//Do Yun Jason Kim
//DSA II, program 2
//heap.h

#ifndef _HEAP_H
#define _HEAP_H

#include <vector>
#include <string>
#include "hash.h"

class heap
{
    public:
        //given in class
        heap(int capacity);
        int insert(const std::string &id, int key, void *pv = NULL);
        int setKey(const std::string &id, int key);
        int deleteMin(std::string *pId = NULL, int *pKey = NULL, void *ppData = NULL);
        int remove(const std::string &id, int *pKey = NULL, void *ppData = NULL);

    private:
        class node
        //class for pointers
        {
            public:
                //define the ID of a node, the key of the node, and the pointer to the data
                std::string id;
                int key;
                void *pData;
        };
        //define current size of heap as capacity
        //define the number of elements in the heap as filled
        int capacity;
        int filled;
        //define the binary heap
        std::vector<node> data;
        //map ids to pointers
        hashTable *mapping;
        //percolate functions
        void percUp(int posCur);
        void percDown(int posCur);
        //getting the position of heap
        int getPos(node *pn);
};
#endif
