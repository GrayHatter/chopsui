# Defaults
CC=cc
_CFLAGS=-Wall -Wextra -Werror -Wno-unused-parameters \
		-std=c11 -Iinclude/
CFLAGS?=-g
LD=ld
LDFLAGS=
AR=ar
ARFLAGS=srv

# User settings
sinclude config.mk

CFLAGS:=$(_CFLAGS) $(CFLAGS)

%.o: %.c
	$(CC) -c -o $@ $(INCLUDE) $(CFLAGS) $<

include parse/Makefile
include util/Makefile

libchopsui.so: $(ARCHIVES)
	$(LD) -shared $(LDFLAGS) -o $@ $<

libchopsui.a: $(ARCHIVES)
	$(AR) $(ARFLAGS) $@ $<

all: libchopsui.so libchopsui.a

clean:
	find . -name "*.o" -delete
	find . -name "*.a" -delete
	find . -name "*.so" -delete

.PHONY: all clean

.DEFAULT_GOAL=all
