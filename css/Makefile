ARCHIVES+= css/css.a

OBJECTS=css/color_parse.o \
		css/css_parse.o \
		css/scalar_parse.o \
		css/selector_parse.o \
		css/keyframes_free.o \
		css/media_rule_free.o \
		css/selector_free.o \
		css/stylesheet_free.o \
		css/style_rule_free.o \
		css/scalar_normalize.o \
		css/selector_print.o \
		css/css_parse_ch.o \
		css/parse_comment.o \
		css/parse_document.o \
		css/parse_properties.o

css/css.a: $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $?

CSS_LIBS=css/css.a
