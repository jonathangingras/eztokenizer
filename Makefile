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
	@cat test.txt
	@echo ---
	@cat test.txt | ./$< 0
	@echo ---
	@cat test.txt | ./$< 1
	@echo ---
	@cat test.txt | ./$< 2
	@echo ---
	@cat test.txt | ./$< 3
	@echo ---
	@cat test.txt | ./$< 4
