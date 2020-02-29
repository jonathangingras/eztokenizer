#ifndef _BUFFER_H_
#define _BUFFER_H_

#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BUFFER_UNIT_SIZE 1024

struct buffer {
  char *data;
  size_t size, allocated;
};

struct buffer_memory_input {
  char *input;
  size_t offset, max;
};

void buffer_clear(struct buffer *buffer);
int buffer_empty(struct buffer *buffer);
void buffer_deinit(struct buffer *buffer);
struct buffer *buffer_init(struct buffer *buffer, size_t allocated);
struct buffer *buffer_reset(struct buffer *buffer);
int buffer_increase_allocation(struct buffer *buffer, size_t increase);
char *buffer_last_byte(struct buffer *buffer);
int buffer_add_byte(struct buffer *buffer, char byte);
int buffer_fgetc(struct buffer *buffer, FILE *input);
int buffer_memgetc(struct buffer *buffer, struct buffer_memory_input *input);

#ifdef __cplusplus
}
#endif

#endif
