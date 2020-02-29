#ifndef _WORD_H_
#define _WORD_H_

#include "parse.h"

#ifdef __cplusplus
extern "C" {
#endif

int is_word_separator(char byte);
int on_each_word(int (*on_each)(char *line, size_t len, void *data), void *data, struct byte_reader *reader);

#ifdef __cplusplus
}
#endif

#endif
