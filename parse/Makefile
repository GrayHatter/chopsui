ARCHIVES+= parse/parse.a

OBJECTS=parse/selector_destroy.o \
		parse/selector_parse.o

parse/parse.a: $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $?

PARSE_LIBS=parse/parse.a
