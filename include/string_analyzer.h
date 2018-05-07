

#ifndef __STRING_ANALYZER_H__
#define __STRING_ANALYZER_H__

#include <ctype.h>
#include "bst.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DELIMITERS " \n`~!();:\",.?\0"

bst_t *str_split(const char *str);
bst_t *fstr_split(FILE *fstream);
char *strlow(char *str);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __STRING_ANALYZER_H__ */