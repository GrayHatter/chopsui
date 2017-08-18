ARCHIVES+= $(BDIR)/css/css.a

OBJECTS=$(BDIR)/css/color_parse.o \
		$(BDIR)/css/css_parse.o \
		$(BDIR)/css/scalar_parse.o \
		$(BDIR)/css/selector_parse.o \
		$(BDIR)/css/keyframes_free.o \
		$(BDIR)/css/media_rule_free.o \
		$(BDIR)/css/selector_free.o \
		$(BDIR)/css/stylesheet_free.o \
		$(BDIR)/css/style_rule_free.o \
		$(BDIR)/css/scalar_normalize.o \
		$(BDIR)/css/selector_print.o \
		$(BDIR)/css/css_parse_ch.o \
		$(BDIR)/css/parse_comment.o \
		$(BDIR)/css/parse_document.o \
		$(BDIR)/css/parse_properties.o

$(BDIR)/css/css.a: $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $?

CSS_LIBS=$(BDIR)/css/css.a
