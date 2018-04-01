

#ifndef __STRING_ANALYZER_H__
#define __STRING_ANALYZER_H__

#ifdef __cplusplus
extern "C" {
#endif

void str_split(const char *str, char delimiter, void (*map_function)(const char *, void *), void *arg);
void str_splits(const char *str, const char *delimiters, void (*map_function)(const char *, void *), void *arg);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __STRING_ANALYZER_H__ */