ARCHIVES+= parse/parse.a

OBJECTS=parse/selector_destroy.o \
		parse/selector_parse.o \
		parse/scalar_parse.o \
		parse/stylesheet_parsec.o \
		parse/stylesheet_parse.o \
		parse/color_parse.o

parse/parse.a: $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $?

PARSE_LIBS=parse/parse.a
