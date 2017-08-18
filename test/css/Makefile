$(BDIR)/test_selector_parse: test/main.c test/css/selector_parse.c $(ARCHIVES)
	$(TESTCC) -o $@ $^ $(ARCHIVES)

$(BDIR)/test_scalar_parse: test/main.c test/css/scalar_parse.c $(ARCHIVES)
	$(TESTCC) -o $@ $^ $(ARCHIVES)

$(BDIR)/test_css_parse: test/main.c test/css/css_parse.c $(ARCHIVES)
	$(TESTCC) -o $@ $^ $(ARCHIVES)

TESTS+=$(BDIR)/test_selector_parse
TESTS+=$(BDIR)/test_scalar_parse
TESTS+=$(BDIR)/test_css_parse
