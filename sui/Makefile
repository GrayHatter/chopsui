ARCHIVES+= sui/sui.a

OBJECTS=sui/sui_parse.o \
		sui/sui_node_create.o \
		sui/sui_parse_ch.o \
		sui/parse_node.o \
		sui/parse_str.o

sui/sui.a: $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $?

SUI_LIBS=sui/sui.a
