#include "functionTable.h"
#include <cmath>
#include <cstring>
#include <cassert>

namespace Function
{
    double CoTan(double x)
    {
        double y = std::tan(x);
        if (y == 0)
        {
            std::cout << "cotan of " << x << " undefined\n";
            return HUGE_VAL;
        }
        return 1.0/y;
    }

    struct Entry
    {
        PtrFun pFun;
        char *strFun;
    };

    Entry Array[] =
    {
        std::log, "log",
        std::log10, "log10",
        std::exp, "exp",
        std::sqrt, "sqrt",
        std::sin, "sin",
        std::cos, "cos",
        std::tan, "tan",
        CoTan, "cotan",
        std::sinh, "sinh",
        std::cosh, "cosh",
        std::tanh, "tanh",
        std::asin, "asin",
        std::acos, "acos",
        std::atan, "atan",
        0, ""
    };

    Table::Table(SymbolTable & symTab) : _size(sizeof Array / sizeof Array[0])
    {
        _pFun = new PtrFun [_size];
        for (size_t i = 0; i < _size; ++i)
        {
            int len = std::strlen(Array[i].strFun);
            if (len == 0)
                break;
            _pFun[i] = Array[i].pFun;
            //std::cout << Array[i].strFun << std::endl;
            size_t j = symTab.ForceAdd(Array[i].strFun);
            assert(i == j);
        }
    }
    Table::~Table()
    {
        delete [] _pFun;
    }
}

