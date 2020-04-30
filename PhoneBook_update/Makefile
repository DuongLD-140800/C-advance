.PHONY: all, install, clean  

TARGET = test

HDRS = entry.h phoneBook.h
CSRCS = main.c entry.c

OBJSDIR=./build
OBJS:=$(patsubst %.c, $(OBJSDIR)/%.o, $(CSRCS))

CFLAGS+=-I./include -DDEBUG -Wall -g
LDFLAGS+=-L./lib -lm

CC:=gcc

all: ${TARGET}
$(TARGET):$(OBJS)
      $(CC) $(OBJS) -o $@ $(LDFLAGS)
$(OBJSDIR)/%.o:%.c $(HDRS)
      $(CC) -c $< -o $@ $(CFLAGS)
install:
      cp -rf ${TARGET} /usr/local/bin

clean:  
      rm -rf ${OBJSDIR}/*.o
      rm -rf ${TARGET}  