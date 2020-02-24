.PHONY: clean
CC = gcc
TARGET = test
OBJ = main.o jval.o
DEPS =  main.h jval.h

$(TARGET): $(OBJ) 
	$(CC) -o $@ $(OBJ)
%.o: %.c $(DEPS)
	$(CC) -c $<

clean:
	rm -f $(TARGET) $(OBJ)