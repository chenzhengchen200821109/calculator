#include <iostream>
#include <cmath>
#include "store.h"

Store::Store(SymbolTable& symTab)
{
    std::cout << "e = " << std::exp(1) << std::endl;
    int id = symTab.ForceAdd("e");
    SetValue(id, std::exp(1));
    std::cout << "pi = " << 2.0 * std::acos(0.0) << std::endl;
    id = symTab.ForceAdd("pi");
    AddValue(id, 2.0 * std::acos(0.0));
}

