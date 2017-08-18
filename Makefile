sinclude config.mk

# -Wno-missing-field-initializers to stop clang from errorneously warning on struct = { 0 }
CFLAGS:=-Wall -Wextra -Werror -Wno-unused-parameter -Wno-missing-field-initializers \
	-std=c11 -Iinclude/ -fPIC $(CFLAGS)
BDIR:=.build

$(BDIR)/%.o: %.c
	@mkdir -p $(shell dirname $@)
	$(CC) -c -o $@ $(INCLUDE) -I$(shell dirname $<) $(CFLAGS) $<

include css/Makefile
include node/Makefile
include parser/Makefile
include sui/Makefile
include tree/Makefile
include type/Makefile
include util/Makefile

$(BDIR)/libchopsui.so: $(ARCHIVES)
	$(LD) -shared $(LDFLAGS) -o $@ $^

$(BDIR)/libchopsui.a: $(ARCHIVES)
	$(AR) $(ARFLAGS) $@ $^

all: $(BDIR)/libchopsui.so $(BDIR)/libchopsui.a

clean:
	rm -rf .build
	find . -name "*.o" -delete
	find . -name "*.a" -delete
	find . -name "*.so" -delete
	find test/ -type f -executable -delete

include test/Makefile

check: $(TESTS)
	@find .build/ -name "test_*" -type f -executable -exec \{\} \;

.PHONY: all clean check

.DEFAULT_GOAL=all
