ARCHIVES+= $(BDIR)/util/util.a

OBJECTS=$(BDIR)/util/hashtable.o \
		$(BDIR)/util/list.o \
		$(BDIR)/util/set.o \
		$(BDIR)/util/utf8_chsize.o \
		$(BDIR)/util/utf8_decode.o \
		$(BDIR)/util/utf8_encode.o \
		$(BDIR)/util/utf8_size.o \
		$(BDIR)/util/string.o \
		$(BDIR)/util/hash.o \
		$(BDIR)/util/errors.o

$(BDIR)/util/util.a: $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $?

UTIL_LIBS=$(BDIR)/util/util.a
