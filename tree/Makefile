ARCHIVES+= $(BDIR)/tree/tree.a

OBJECTS=$(BDIR)/tree/node_append_child.o \
		$(BDIR)/tree/node_insert_child.o \
		$(BDIR)/tree/node_detach.o

$(BDIR)/tree/tree.a: $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $?

NODE_LIBS=$(BDIR)/tree/tree.a
