ARCHIVES+= parser/parser.a

OBJECTS=parser/parser_error.o \
		parser/push_parser.o \
		parser/parser_append_ch.o \
		parser/parser_cleanup.o

parser/parser.a: $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $?

PARSER_LIBS=parser/parser.a
