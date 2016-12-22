ARCHIVES+= util/util.a

OBJECTS=util/hashtable.o \
		util/list.o \
		util/set.o \
		util/utf8_chsize.o \
		util/utf8_decode.o \
		util/utf8_encode.o \
		util/utf8_size.o \
		util/get_named_color.o

util/util.a: $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $?

UTIL_LIBS=util/util.a
