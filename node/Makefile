ARCHIVES+= $(BDIR)/node/node.a

OBJECTS=$(BDIR)/node/node_get_attr.o \
		$(BDIR)/node/node_set_attr.o \
		$(BDIR)/node/node_has_class.o \
		$(BDIR)/node/node_add_class.o \
		$(BDIR)/node/node_remove_class.o \
		$(BDIR)/node/node_free.o

$(BDIR)/node/node.a: $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $?

NODE_LIBS=$(BDIR)/node/node.a
