#include "Utils.h"

#include <limits.h>

unsigned long timeDiff(unsigned long now, unsigned long start)
{
    if (start <= now)
        return now - start;
    else
        return (ULONG_MAX - start) + now + 1;
}