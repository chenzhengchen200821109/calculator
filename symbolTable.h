#if !defined _SYMBOLTABLE_H_
#define _SYMBOLTABLE_H_

#include <vector>
#include <cstdlib>
#include <map>
#include <string>
#include "serialize.h"

class SymbolTable
{
    public:
        static const std::size_t idNotFound = 0xffffffff;
        SymbolTable() : _id(0) {}
        std::size_t ForceAdd(std::string const& str);
        std::size_t Find(std::string const& str) const;
        void Serialize(Serializer& out) const;
        void DeSerialize(DeSerializer& in);
    private:
        std::map<std::string, std::size_t> _dictionary;
        std::size_t _id;
};

#endif
