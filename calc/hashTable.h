#if !defined hashTable_h
#define hashTable_h

#include "list.h"

class HTable
{
    //friend class IdSeq;
    public:
        class Seq : public List<int>::Seq
        {
            public:
                Seq(const HTable& htab, const char *str) : List<int>::Seq(htab.Find(str)) {}
        };
    public:
        explicit HTable(int size);
        void Add(const char* str, int id);
        const List<int>& Find(const char* str) const;
        int hash(const char* str) const;
    private:
        List<int>* _aList;
        int _size;
};


#endif
