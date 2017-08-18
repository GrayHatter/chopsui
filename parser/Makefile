ARCHIVES+= $(BDIR)/parser/parser.a

OBJECTS=$(BDIR)/parser/parser_error.o \
		$(BDIR)/parser/push_parser.o \
		$(BDIR)/parser/parser_pop.o \
		$(BDIR)/parser/parser_push_ch.o \
		$(BDIR)/parser/parser_pop_ch.o \
		$(BDIR)/parser/parser_peek_ch.o \
		$(BDIR)/parser/parser_far_peek_ch.o \
		$(BDIR)/parser/parser_buffer_empty.o \
		$(BDIR)/parser/parser_cleanup.o \
		$(BDIR)/parser/parser_init.o \
		$(BDIR)/parser/parse_ch.o

$(BDIR)/parser/parser.a: $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $?

PARSER_LIBS=$(BDIR)/parser/parser.a
