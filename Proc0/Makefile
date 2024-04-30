# Proc-0 Makefile.

ifndef TOP
 TOP = .
 INCLUDED = no
endif

ifeq ($(findstring $(MAKECMDGOALS),clean distclean),)
 include $(TOP)/config.mak
endif

all: config.mak proc0

proc0: proc0.c
	gcc -O2 -Wall -g -o $@ $< -ldl

config.mak:
	$(if $(wildcard $@),,@echo "Please run ./configure script." && exit 1)

clean:
	git clean -xdf
