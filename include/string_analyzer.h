

#ifndef __STRING_ANALYZER_H__
#define __STRING_ANALYZER_H__

#include "bst.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DELIMITERS " .,?!/\\\"'\n"

bst_t *str_split(const char *str);
bst_t *fstr_split(FILE *fstream);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __STRING_ANALYZER_H__ */