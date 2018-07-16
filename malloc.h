#if !defined MALLOC_H
#define MALLOC_H
#include <cstdlib>

void * operator new(std::size_t size)
{
    void *p = std::malloc(size);
    if (Tracer::Ready)
        NewTrace.Add(p, "?", 0);
    return p;
}

void operator delete(void * p)
{
    if (Tracer::Ready)
        NewTrace.Remove(p);
    std::free(p);
}

void * operator new(std::size_t size, char const * file, int line)
{
    void * p = std::malloc(size);
    if (Tracer::Ready)
        NewTrace.Add(p, file, line);
    return p;
}

void operator delete(void * p, char const *, int)
{
    if (Tracer::Ready)
        NewTrace.Remove(p);
    std::free(p);
}

#endif
