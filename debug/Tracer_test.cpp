#include "DebugNew.h"
#if !defined NDEBUG
Tracer NewTrace;
#endif

int main()
{
    int * p = new int;

    return 0;
}
