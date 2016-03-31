#!/bin/sh

gcc -Wall -pedantic \
	-o licence \
	comments.c errors.c extensions.c licences.c main.c \
	-O3
