ARCHIVES+= node/node.a

OBJECTS=node/node_get_attr.o \
		node/node_set_attr.o \
		node/node_has_class.o \
		node/node_add_class.o \
		node/node_remove_class.o \
		node/node_free.o

node/node.a: $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $?

NODE_LIBS=node/node.a
