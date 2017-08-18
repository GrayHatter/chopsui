sinclude config.mk

# -Wno-missing-field-initializers to stop clang from errorneously warning on struct = { 0 }
CFLAGS:=-Wall -Wextra -Werror -Wno-unused-parameter -Wno-missing-field-initializers \
	-std=c11 -Iinclude/ -fPIC $(CFLAGS)
BDIR:=.build

$(BDIR)/%.o: %.c $(BDIR)/%.d
	@mkdir -p $(shell dirname $@)
	$(CC) -c -o $@ $(INCLUDE) -I$(shell dirname $<) $(CFLAGS) $<
	@$(CC) $(CFLAGS) -MF"$@.d" -MG -MM -MP -MT"$@" $<
	@touch $@.d

$(BDIR)/%.d: ;

.PRECIOUS: $(BDIR)/%.d
sinclude $(shell find $(BDIR) -name "*.d" 2>/dev/null || true)

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

tags: $(BDIR)/libchopsui.a
	@find . -name "*.c" | xargs ctags || true

all: $(BDIR)/libchopsui.so $(BDIR)/libchopsui.a tags

clean:
	rm -rf .build

include test/Makefile

check: $(TESTS)
	@find .build/ -name "test_*" -type f -executable -exec \{\} \;

.PHONY: all clean check

.DEFAULT_GOAL=all
