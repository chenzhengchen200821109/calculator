#if !defined store_h
#define store_h

#include "symbolTable.h"
#include <cassert>
#include <vector>
#include <cstdlib>

class Store
{
    public:
        explicit Store(SymbolTable& symTab);
        bool IsInit(std::size_t id) const
        {
            assert(id != SymbolTable::idNotFound);
            return id < _isInit.size() && _isInit[id];
        }
        double Value(std::size_t id) const
        {
            assert(id >= 0);
            assert(IsInit(id));
            return _cell[id];
        }
        void SetValue(std::size_t id, double val)
        {
            assert(id >= 0);
            if (IsInit(id))
            {
                _cell[id] = val;
                _isInit[id] = true;
            }
            else
            {
                AddValue(id, val);
            }
        }
        void AddValue(std::size_t id, double val)
        {
            assert(id >= 0);
            _cell.resize(id + 1);
            _isInit.resize(id + 1);
            _cell[id] = val;
            _isInit[id] = true;
        }
    private:
        std::vector<double> _cell;
        std::vector<bool> _isInit;
};


#endif
