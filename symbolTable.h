#if !defined symbolTable_h
#define symbolTable_h

#include <vector>
#include <cstdlib>
#include <map>
#include <string>

class SymbolTable
{
    public:
        static const std::size_t idNotFound = 0xffffffff;
        SymbolTable() : _id(0) {}
        std::size_t ForceAdd(std::string const& str);
        std::size_t Find(std::string const& str) const;
    private:
        std::map<std::string, std::size_t> _dictionary;
        std::size_t _id;
};

#endif
