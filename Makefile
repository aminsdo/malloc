CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99 -fPIC -fvisibility=hidden -fno-builtin -g
LDFLAGS = -shared
TARGET_LIB = libmalloc.so
OBJS = malloc.o malloc_func.o malloc_tool.o free_func.o realloc_func.o
VPATH=src/

.PHONY: all ${TARGET_LIB} clean check

check: ${TARGET_LIB}
	tests/test.sh

${TARGET_LIB}: ${OBJS}
	${CC} ${LDFLAGS} -o $@ $^

all: ${TARGET_LIB}

clean:
	${RM} ${TARGET_LIB} ${OBJS}
