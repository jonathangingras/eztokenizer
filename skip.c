#include "skip.h"

int on_each_with_skips(char *unit, size_t len, void *skip_wrapper) {
  struct skip_wrapper *wrapper;

  wrapper = (struct skip_wrapper *)skip_wrapper;

  if (wrapper->should_skip(unit, len, wrapper->data)) {
    return 0;
  }

  return wrapper->on_each(unit, len, wrapper->data);
}
