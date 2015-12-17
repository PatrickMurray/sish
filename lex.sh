#! /usr/bin/env bash
make fclean
lex parser.c
make
make clean
