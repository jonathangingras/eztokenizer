#include <string.h>
#include "buffer.h"

void buffer_clear(struct buffer *buffer) {
  memset(buffer->data, 0, buffer->allocated);
}

int buffer_empty(struct buffer *buffer) {
  return buffer->size == 0;
}

void buffer_deinit(struct buffer *buffer) {
  if (buffer->allocated > 0) {
    free(buffer->data);
    buffer->allocated = 0;
    buffer->size = 0;
  }
}

struct buffer *buffer_init(struct buffer *buffer, size_t allocated) {
  buffer->data = malloc(allocated);
  if(!buffer->data) {
    return NULL;
  }
  buffer->data[0] = 0;
  buffer->size = 0;
  buffer->allocated = allocated;
  buffer_clear(buffer);
  return buffer;
}

struct buffer *buffer_reset(struct buffer *buffer) {
  char *data;

  if(buffer->allocated > BUFFER_UNIT_SIZE){
    data = realloc(buffer->data, BUFFER_UNIT_SIZE);
    if(data == NULL) {
      return NULL;
    }

    buffer->data = data;
    buffer->allocated = BUFFER_UNIT_SIZE;
  }

  buffer->size = 0;
  buffer_clear(buffer);

  return buffer;
}

int buffer_increase_allocation(struct buffer *buffer, size_t increase) {
  char *data;
  data = NULL;
  data = realloc(buffer->data, buffer->allocated + increase);
  if (!data) {
    return -1;
  }
  buffer->data = data;
  buffer->allocated += increase;
  return 0;
}

char *buffer_last_byte(struct buffer *buffer) {
  if(buffer->size == 0) {
    return NULL;
  }
  return &(buffer->data[buffer->size - 1]);
}

int buffer_add_byte(struct buffer *buffer, char byte) {
  int err;

  err = 0;

  while(buffer->size + 1 >= buffer->allocated) {
    if((err = buffer_increase_allocation(buffer, BUFFER_UNIT_SIZE))) {
      return err;
    }
  }

  buffer->data[buffer->size] = byte;
  ++buffer->size;
  return 0;
}

int buffer_fgetc(struct buffer *buffer, FILE *input) {
  int err;
  int byte;

  err = 0;

  if((byte = fgetc(input))) {
    if(ferror(input) || feof(input)) {
      return -1;
    }

    if((err = buffer_add_byte(buffer, byte))) {
      return err;
    }
  }

  return 0;
}

int buffer_memgetc(struct buffer *buffer, struct buffer_memory_input *input) {
  int byte;
  int err;

  if(input->offset >= input->max) {
    return -1;
  }

  byte = input->input[input->offset];
  ++input->offset;

  err = 0;

  if((err = buffer_add_byte(buffer, byte))) {
    return err;
  }

  return 0;
}
