#include <stdio.h>
#include <stdlib.h>
#include "line.h"
#include "word.h"

struct text_position {
  FILE *output;
  size_t line, word, wanted_column;
};

static int for_each_word(char *word, size_t len, struct text_position *position) {
  if (position->word == position->wanted_column) {
      fprintf(position->output, "%s", word);
  }

  ++position->word;

  return 0;
}

static int for_each_line(char *line, size_t len, struct text_position *position) {
  struct buffer_memory_input input = {
    .input = line,
    .offset = 0,
    .max = len,
  };

  struct byte_reader reader = {
    .read_byte = (int (*)(struct buffer *, void *))&buffer_memgetc,
    .input = &input,
  };

  if (position->line > 0) {
    fprintf(position->output, "\n");
  }

  ++position->line;
  position->word = 0;

  return on_each_word((int (*)(char *, size_t, void *))&for_each_word, position, &reader);
}

static int print_column(FILE *output, int column_index, FILE *input) {
  int err;

  struct text_position position = {
    .output = output,
    .line = 0,
    .word = 0,
    .wanted_column = (size_t)column_index,
  };

  struct byte_reader reader = {
    .read_byte = (int (*)(struct buffer *, void *))&buffer_fgetc,
    .input = input,
  };

  if ((err = on_each_line((int (*)(char *, size_t, void *))&for_each_line, &position, &reader))) {
    return err;
  }

  if (position.line > 0) {
    fprintf(output, "\n");
  }

  return 0;
}

int main(int argc, char **argv) {
  int column_index;

  if (argc != 2) {
    return 1;
  }

  column_index = -1;
  column_index = atoi(argv[1]);

  if (column_index == -1) {
    return 2;
  }

  return print_column(stdout, column_index, stdin);
}
