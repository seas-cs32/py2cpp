all: main

CC = clang
override CFLAGS += -g -Wno-everything -pthread -lm

SRCS = $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.c' -print)
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

%.d: %.c
	@set -e; rm -f $@; \
	$(CC) -MM $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

include $(DEPS)

main: main.o
	$(CC) $(CFLAGS) main.o -o "$@"

main-debug: main.o
	$(CC) $(CFLAGS) -O0 main.o -o "$@"

mycode: mycode.o
	$(CC) $(CFLAGS) mycode.o -o "$@"

clean:
	rm -f $(OBJS) $(DEPS) main main-debug mycode