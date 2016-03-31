#!/bin/sh

gcc -Wall -pedantic -std=c11 \
	-o licence \
	comments.c errors.c extensions.c licences.c main.c \
	-O3
