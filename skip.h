#ifndef _SKIP_H_
#define _SKIP_H_

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

struct skip_wrapper {
  int (*on_each)(char *unit, size_t len, void *data);
  int (*should_skip)(char *unit, size_t len, void *data);
  void *data;
};

int on_each_with_skips(char *unit, size_t len, void *skip_wrapper);

#ifdef __cplusplus
}
#endif

#endif
