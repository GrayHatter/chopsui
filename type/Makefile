ARCHIVES+= $(BDIR)/type/type.a

OBJECTS=$(BDIR)/type/impl.o

$(BDIR)/type/type.a: $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $?

NODE_LIBS=$(BDIR)/type/type.a
