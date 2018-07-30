//#include "list.h"
#include "hashTable.h"
#include <cassert>

HTable::HTable(int size) : _size(size)
{
    _aList = new List<int> [size];
}

const List<int>& HTable::Find(const char* str) const
{
    int i = hash(str);
    return _aList[i];
}

void HTable::Add(const char* str, int id)
{
    int i = hash(str);
    _aList[i].Add(id);
}

int HTable::hash(const char* str) const
{
    assert(str != 0 && str[0] != 0);
    unsigned h = str[0];
    for (int i = 1; str[i] != 0; ++i)
        h = (h << 4) + str[i];
    return h % _size;
}

