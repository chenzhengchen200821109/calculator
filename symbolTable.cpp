#include "symbolTable.h"
#include "idSeq.h"
#include <cassert>
#include <iostream>

std::size_t SymbolTable::ForceAdd(std::string const& str)
{
    std::string s(str);
    _dictionary[s] = _id;
    return _id++;
}

std::size_t SymbolTable::Find(std::string const& str) const
{
    std::map<std::string, std::size_t>::const_iterator it;
    it = _dictionary.find(str);
    if (it != _dictionary.end())
        return it->second;
    return idNotFound;
}

