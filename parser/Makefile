ARCHIVES+= parser/parser.a

OBJECTS=parser/parser_error.o \
		parser/push_parser.o \
		parser/parser_push_ch.o \
		parser/parser_pop_ch.o \
		parser/parser_peek_ch.o \
		parser/parser_far_peek_ch.o \
		parser/parser_buffer_empty.o \
		parser/parser_cleanup.o \
		parser/parser_init.o \
		parser/parse_ch.o

parser/parser.a: $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $?

PARSER_LIBS=parser/parser.a
