ARCHIVES+= $(BDIR)/sui/sui.a

OBJECTS=$(BDIR)/sui/sui_parse.o \
		$(BDIR)/sui/sui_node_create.o \
		$(BDIR)/sui/sui_parse_ch.o \
		$(BDIR)/sui/parse_node.o \
		$(BDIR)/sui/parse_string.o \
		$(BDIR)/sui/parse_attr.o

$(BDIR)/sui/sui.a: $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $?

SUI_LIBS=$(BDIR)/sui/sui.a
