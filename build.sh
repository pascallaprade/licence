#!/bin/sh

gcc -Wall -pedantic -std=c99 \
	-o licence \
	src/comments.c src/errors.c src/extensions.c src/licenses.c src/main.c \
	src/prepend.c src/utils.c \
	-O3
