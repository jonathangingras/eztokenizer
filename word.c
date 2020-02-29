#include "word.h"
#include "skip.h"

int is_word_separator(char byte) {
  return byte == ' ' || byte == '\t';
}

static int should_stop_after_padding(char *buffer, size_t len, void *data) {
  return is_word_separator(buffer[len-1]);
}

static int should_skip_empty_word(char *unit, size_t len, void *data) {
  return len == 0 || (len == 1 && is_word_separator(unit[len-1]));
}

int on_each_word(int (*on_each)(char *line, size_t len, void *data), void *data, struct byte_reader *reader) {
  struct skip_wrapper wrapper = {
    .on_each = on_each,
    .should_skip = &should_skip_empty_word,
    .data = data,
  };

  return parse(&should_stop_after_padding, &on_each_with_skips, &wrapper, reader);
}
