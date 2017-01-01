sinclude config.mk

# -Wno-missing-field-initializers to stop clang from errorneously warning on struct = { 0 }
CFLAGS:=-Wall -Wextra -Werror -Wno-unused-parameter -Wno-missing-field-initializers \
	-std=c11 -Iinclude/ -fPIC $(CFLAGS)

%.o: %.c
	$(CC) -c -o $@ $(INCLUDE) -I$(shell dirname $<) $(CFLAGS) $<

include css/Makefile
include node/Makefile
include tree/Makefile
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
	find test/ -type f -executable -delete

include test/Makefile

check: $(TESTS)
	@find test/ -type f -executable -exec \{\} \;

.PHONY: all clean check

.DEFAULT_GOAL=all
