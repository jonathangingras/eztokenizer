#include "parse.h"

static int execute_on_stop(struct buffer *buffer,
                       int (*on_stop)(char *line, size_t len, void *data),
                       void *data) {
  int err;

  if((err = buffer_add_byte(buffer, 0))) {
    buffer_deinit(buffer);
    return err;
  }

  if((err = on_stop(buffer->data, buffer->size-1, data))) {
    buffer_deinit(buffer);
    return err;
  }

  buffer_reset(buffer);

  return 0;
}

int parse(int (*should_stop)(char *buffer, size_t len, void *data),
          int (*on_stop)(char *line, size_t len, void *data),
          void *data,
          struct byte_reader *reader) {
  struct buffer buffer;
  int err;
  char *byte;

  err = 0;

  if(!buffer_init(&buffer, BUFFER_UNIT_SIZE)) {
    return -1;
  }

  while (reader->read_byte(&buffer, reader->input) == 0) {
    byte = buffer_last_byte(&buffer);

    if(byte == NULL) {
      return -2;
    }

    if(should_stop(buffer.data, buffer.size, data)) {
      if((err = execute_on_stop(&buffer, on_stop, data))) {
        return err;
      }
    }
  }

  if(!buffer_empty(&buffer)) {
    if((err = execute_on_stop(&buffer, on_stop, data))) {
      return err;
    }
  }

  buffer_deinit(&buffer);

  return 0;
}
