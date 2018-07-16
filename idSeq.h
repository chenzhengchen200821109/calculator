#if !defined listSeq_h
#define listSeq_h

#include "hashTable.h"
#include "list.h"

class IdSeq : public List<int>::Seq
{
    public:
        IdSeq(const HTable& htab, const char* str) : List<int>::Seq(htab.Find(str)) {}
};

#endif
