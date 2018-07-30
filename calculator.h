#ifndef _CALCULATOR_H
#define _CALCULATOR_H

#include "symbolTable.h"
#include "functionTable.h"
#include "store.h"
#include "serialize.h"

class Calculator
{
    friend class Parser;
    public:
        Calculator() : _funTab(_symTab), _store(_symTab) {}
        void Serialize(Serializer& out)
        {
            _symTab.Serialize(out);
            _store.Serialize(out);
        }
        void DeSerialize(DeSerializer& in)
        {
            _symTab.DeSerialize(in);
            _store.DeSerialize(in);
        }
    private:
        Store& GetStore() { return _store; }
        PtrFun GetFun(std::size_t id) const
        {
            return _funTab.GetFun(id);
        }
        bool IsFunction(std::size_t id) const
        {
            return id < _funTab.Size();
        }
        std::size_t AddSymbol(std::string const& str)
        {
            return _symTab.ForceAdd(str);
        }
        std::size_t FindSymbol(std::string const& str) const
        {
            return _symTab.Find(str);
        }
        SymbolTable _symTab;
        Function::Table _funTab;
        Store _store;
};

#endif
