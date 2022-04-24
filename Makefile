.PHONY: all clean rebuild

ROOT := $(realpath .)

SRC_FILES := $(wildcard ${ROOT}/library/*.c) $(wildcard $(ROOT)/projects/*.c) main.c

all:
	g++ -o

clean:
	rm -rf ${ROOT}/build

rebuild:
	${MAKE} clean
	${MAKE} all
