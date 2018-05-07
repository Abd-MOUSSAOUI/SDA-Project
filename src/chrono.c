

#include "chrono.h"

timeinterval_t now()
{
    timeinterval_t tv;
    gettimeofday(&tv, NULL);
    return tv;
}

llu_t time_elapsed(timeinterval_t begin, timeinterval_t end, timeunit unit)
{
    llu_t t;
    switch (unit)
    {
        case SECONDS:
            t = (llu_t)((llu_t)end.tv_sec + (llu_t)end.tv_usec / (llu_t)1000000 - (llu_t)begin.tv_sec - (llu_t)begin.tv_usec / (llu_t)1000000);
        case MILLISECONDS:
            t = (llu_t)((llu_t)end.tv_sec * 1000 + (llu_t)end.tv_usec / (llu_t)1000 - (llu_t)begin.tv_sec * 1000 - (llu_t)begin.tv_usec / (llu_t)1000);
        case MICROSECONDS:
            t = (llu_t)((llu_t)end.tv_sec * 1000000 + (llu_t)end.tv_usec - (llu_t)begin.tv_sec * 1000000 - (llu_t)begin.tv_usec);
    }
    return t / 1000;
}

#ifdef __clang__
llu_t measure_time(timeunit unit, void(^block)(void))
#else
llu_t measure_time(timeunit unit, void(*block)(void))
#endif
{
    timeinterval_t begin = now();
    block();
    timeinterval_t end = now();
    return time_elapsed(begin, end, unit);
}