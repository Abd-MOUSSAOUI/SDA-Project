#ifndef __CHRONO_H__
#define __CHRONO_H__

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned long long llu_t;

typedef struct timeval timeinterval_t;

typedef enum { SECONDS, MILLISECONDS, MICROSECONDS } timeunit;

timeinterval_t now();

llu_t time_elapsed(timeinterval_t begin, timeinterval_t end, timeunit unit);

#ifdef __clang__
llu_t measure_time(timeunit unit, void(^block)(void));
#else
llu_t measure_time(timeunit unit, void(*block)(void));
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __CHRONO_H__ */