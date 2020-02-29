CFLAGS ?= -O3 -std=c89
MAIN = coln
SOURCE = $(wildcard *.c)
SOURCE_OBJ = $(patsubst %.c,%.o,$(SOURCE))

.INTERMEDIATE: $(SOURCE_OBJ)

$(MAIN): $(SOURCE_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(MAIN)

test: $(MAIN)
	@echo "test:"
	@echo "he hello  \nyo yo s\n 67 hety h yehh  fasdfd\n 5"
	@echo ---
	@echo "he hello  \nyo yo s\n 67 hety h yehh  fasdfd\n 5" | ./$< 0
	@echo ---
	@echo "he hello  \nyo yo s\n 67 hety h yehh  fasdfd\n 5" | ./$< 1
	@echo ---
	@echo "he hello  \nyo yo s\n 67 hety h yehh  fasdfd\n 5" | ./$< 2
	@echo ---
	@echo "he hello  \nyo yo s\n 67 hety h yehh  fasdfd\n 5" | ./$< 3
	@echo ---
	@echo "he hello  \nyo yo s\n 67 hety h yehh  fasdfd\n 5" | ./$< 4
