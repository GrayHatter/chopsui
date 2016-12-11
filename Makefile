sinclude config.mk

CFLAGS:=-Wall -Wextra -Werror -Wno-unused-parameter \
	-std=c11 -Iinclude/ -fPIC $(CFLAGS)

%.o: %.c
	$(CC) -c -o $@ $(INCLUDE) $(CFLAGS) $<

include parse/Makefile
include util/Makefile

libchopsui.so: $(ARCHIVES)
	$(LD) -shared $(LDFLAGS) -o $@ $^

libchopsui.a: $(ARCHIVES)
	$(AR) $(ARFLAGS) $@ $^

all: libchopsui.so libchopsui.a

clean:
	find . -name "*.o" -delete
	find . -name "*.a" -delete
	find . -name "*.so" -delete

include test/Makefile

check: $(TESTS)
	find test/ -type f -executable -exec \{\} \;

.PHONY: all clean check

.DEFAULT_GOAL=all
