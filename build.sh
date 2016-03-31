#!/bin/sh

gcc -Wall -pedantic -std=c99 \
	-o licence \
	comments.c errors.c extensions.c licenses.c main.c \
	-O3
