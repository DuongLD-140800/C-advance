.PHONY: clean

CC = gcc
TARGET = test
OBJ = main.o entry.o
DEPS = phoneBook.h entry.h

$(TARGET): $(OBJ)
	$(CC)	-o	$@	$(OBJ)
%.o: %.c	$(DEPS)
	$(CC)	-c	$<

clean:
	rm -f $(OBJ)
	rm -f $(TARGET)
