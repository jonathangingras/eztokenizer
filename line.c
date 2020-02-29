#include "line.h"
#include "skip.h"

static int is_endline(char byte) {
  return byte == '\n';
}

static int should_stop_after_end_line(char *buffer, size_t len, void *data) {
  return is_endline(buffer[len-1]);
}

static int should_skip_empty_line(char *unit, size_t len, void *data) {
  return len == 0 || (len == 1 && is_endline(unit[len-1]));
}

int on_each_line(int (*on_each)(char *line, size_t len, void *data), void *data, struct byte_reader *reader) {
  struct skip_wrapper wrapper = {
                                 .on_each = on_each,
                                 .should_skip = &should_skip_empty_line,
                                 .data = data,
  };

  return parse(&should_stop_after_end_line, &on_each_with_skips, &wrapper, reader);
}
