//		data[hashindex].isDeleted = false;
	//	data[hashindex].pv = pv;

	/*getPointer
void* hashTable::getPointer(const std::string &key, bool *b)
{
	int keyPos = findPos(key);
	if (keyPos == -1 || data[keyPos].isDeleted)
    {
		*b = false;
		return NULL;
	}
	else
    {
		*b = true;
		return data[keyPos].pv;
	}
}

//setPointer
int hashTable::setPointer(const std::string &key, void *pv)
{
	int keyPos = findPos(key);
	if (keyPos == -1)
		return 1;
	else
    {
		data[keyPos].pv = pv;
		return 0;
	}
}

//Remove-Delete
bool hashTable::remove(const std::string &key)
{
	int keyPos = findPos(key);
	if (keyPos == -1)
		return false;
	else
    {
		data[keyPos].isDeleted = true;
		return true;
	}
}
*/
