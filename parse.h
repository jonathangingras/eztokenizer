#ifndef _PARSE_H_
#define _PARSE_H_

#include "buffer.h"

#ifdef __cplusplus
extern "C" {
#endif

struct byte_reader {
  void *input;
  int (*read_byte)(struct buffer *buffer, void *input);
};

int parse(int (*should_stop)(char *buffer, size_t len, void *data),
          int (*on_stop)(char *line, size_t len, void *data),
          void *data,
          struct byte_reader *reader);

#ifdef __cplusplus
}
#endif

#endif
