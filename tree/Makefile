ARCHIVES+= tree/tree.a

OBJECTS=tree/node_append_child.o \
		tree/node_insert_child.o \
		tree/node_detach.o

tree/tree.a: $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $?

NODE_LIBS=tree/tree.a
