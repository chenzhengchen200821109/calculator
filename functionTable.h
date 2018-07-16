#ifndef functionTable_h
#define functionTable_h

#include <iostream>
#include "symbolTable.h"

typedef double (*PtrFun)(double);

namespace Function
{
    class Table
    {
        public:
            Table(SymbolTable & symTab);
            ~Table();
            int Size() const { return _size; }
            PtrFun GetFun(int id) const { return _pFun[id]; }
        private:
            PtrFun *_pFun;
            int _size;
    };
}

#endif
