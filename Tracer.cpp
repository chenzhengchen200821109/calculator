#include <iostream>
#include "Tracer.h"

bool Tracer::Ready = false;

Tracer::Tracer() : _lockCount(0)
{
    Ready = true;
}

Tracer::~Tracer()
{
    Ready = false;
    Dump();
}

void Tracer::Add(void * p, char const * file, int line)
{
    if (_lockCount > 0)
        return;
    Tracer::Lock lock(*this);
    _map [p] = Entry(file, line);
}

void Tracer::Remove(void * p)
{
    if (_lockCount > 0)
        return;
    Tracer::Lock lock(*this);
    iterator it = _map.find(p);
    if (it != _map.end())
    {
        _map.erase(it);
    }
}

void Tracer::Dump()
{
    if (_map.size() != 0)
    {
        std::cerr << "*** Memory leak(s):\n";
        for (iterator it = _map.begin(); it != _map.end(); ++it) {
            char const * file = it->second.File();
            int line = it->second.Line();
            unsigned int addr = reinterpret_cast<unsigned int>(it->first);
            std::cerr << "0x" << std::hex << addr << ": " << file << ", line " << std::dec << line << std::endl;
        }
        std::cerr << std::endl;
    }
}





