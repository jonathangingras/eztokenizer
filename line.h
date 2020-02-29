#ifndef _LINE_H_
#define _LINE_H_

#include "parse.h"

#ifdef __cplusplus
extern "C" {
#endif

int on_each_line(int (*on_each)(char *line, size_t len, void *data), void *data, struct byte_reader *reader);

#ifdef __cplusplus
}
#endif

#endif
