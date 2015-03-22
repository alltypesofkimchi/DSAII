#include <iostream>
#include "hash.h"
using namespace std;

hashTable::hashTable(int size)
{
	capacity = getPrime(size);
	data.resize(capacity);
	filled = 0;
	for (int i=0; i<data.size(); i++)
		data[i].isOccupied = false;
}

//Define insert
int hashTable::insert(const std::string &key, void *pv)
{
	bool success;
	if (contains(key))
		return 1;
	if (filled >= capacity/2)
    {
		success = rehash();
		if(!success)
			return 2;
	}
	int hashindex = hash(key);
	while (data[hashindex].isOccupied)
	{
		hashindex++;
		hashindex %= capacity;
	}
	if (!data[hashindex].isOccupied)
	{
	    //cout << "inserted f " << key << " " << hashindex << endl;
		data[hashindex].key = key;
		data[hashindex].pv = pv;
		data[hashindex].isOccupied = true;
		data[hashindex].isDeleted = false;
		filled++;
		return 0;
	}
	return -1;
}

//Define bool contains
bool hashTable::contains(const std::string &key)
{
    if (findPos(key) > -1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void* hashTable::getPointer(const std::string &key, bool *b)
{
    int pos = findPos(key);
    if(pos == -1||data[pos].isDeleted)
    {
        *b = false;
        return NULL;
    }
    else
    {
        *b = true;
        return data[pos].pv;
    }
}

int hashTable::setPointer(const std::string &key, void *pv)
{
    int pos = findPos(key);
    if (pos == -1)
        return 1;
    else
    {
        data[pos].pv = pv;
        return 0;
    }
}

bool hashTable::remove(const std::string &key)
{
    int pos = findPos(key);
    if(pos == -1)
        return false;
    else
    {
        data[pos].isDeleted = true;
        data[pos].isOccupied = false;
        return true;
    }
}

// Hash Function
int hashTable::hash(const std::string &key)
{
	int hashvalue = 0;
	for(int i=0; i<key.length(); i++)
		hashvalue = 37*hashvalue+key[i];
	hashvalue %= capacity;
	if (hashvalue<0)
		hashvalue += capacity;
	return hashvalue;
}

// Position Find
int hashTable::findPos(const std::string &key)
{
	int hashvalue = hash(key);
	while (data[hashvalue].isOccupied && !data[hashvalue].isDeleted)
    {
        if(data[hashvalue].key == key)
            return hashvalue;
        hashvalue++;
        //cout << "find z " << key << " " << hashvalue << endl;
        if (hashvalue == capacity) {hashvalue = 0;}
	}
	return -1;
	/*
	cout << "hashvalue: " << hashvalue << ", isOccupied: " << !data[hashvalue].isOccupied << endl;
	if(!data[hashvalue].isOccupied)
    {
        //cout << "occupied" <<endl;
        //cout << key << endl;
        return -1;
    }
	while (data[hashvalue].isOccupied)
    {
        cout << "While: "
        if (data[hashvalue].key == key && !data[hashvalue].isDeleted)
            return hashvalue;
		hashvalue++;
		hashvalue %= capacity;
	}
	//cout << "reached end" <<endl;
	return -1;
	*/
}

// Rehash Function
bool hashTable::rehash()
{
	vector<hashItem> oldHashTable = data;
	unsigned int oldSize = oldHashTable.size();
	filled = 0;
	unsigned int nextSize = getPrime(capacity);
	data.resize(1);
	data[0].isOccupied = false;
	data.resize(nextSize);
	capacity = nextSize;
	for (int i=0; i<oldSize; i++)
    {
		if (oldHashTable[i].isOccupied)
        {
			insert(oldHashTable[i].key, oldHashTable[i].pv);
		}
	}
	oldHashTable.clear();
	return true;
}

// Prime numbers
unsigned int hashTable::getPrime(int size)
{
    unsigned int primes[7] = {100003,505919,1054007,2380481,4114741,6699197,8487821};
	for (int i=0; i<6; i++)
    {
		if(primes[i]>size)
			return primes[i];
	}
	return 0;
}
