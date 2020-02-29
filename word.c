#include "word.h"
#include "skip.h"
#include "clean.h"

int is_word_separator(char byte) {
  return byte == ' ' || byte == '\t';
}

static int should_stop_after_separator(char *buffer, size_t len, void *data) {
  return is_word_separator(buffer[len-1]);
}

static int should_skip_empty_word(char *unit, size_t len, void *data) {
  return len == 0 || (len == 1 && is_word_separator(unit[len-1]));
}

static int clean_padding(char **unit, size_t *len, void *data) {
  if ((*len) > 1 && is_word_separator((*unit)[(*len)-1])) {
    (*unit)[(*len)-1] = 0;
    --(*len);
  }
  return 0;
}

int on_each_word(int (*on_each)(char *line, size_t len, void *data), void *data, struct byte_reader *reader) {
  struct skip_wrapper skip_wrapper = {
    .on_each = on_each,
    .should_skip = &should_skip_empty_word,
    .data = data,
  };

  struct clean_wrapper clean_wrapper = {
    .on_each = &on_each_with_skips,
    .clean = &clean_padding,
    .data = &skip_wrapper,
  };

  return parse(&should_stop_after_separator, &on_each_with_cleans, &clean_wrapper, reader);
}
