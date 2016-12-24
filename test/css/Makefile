test/css/test_selector_parse: test/main.c test/css/selector_parse.c $(ARCHIVES)
	$(TESTCC) -o $@ $^ $(ARCHIVES)

test/css/test_scalar_parse: test/main.c test/css/scalar_parse.c $(ARCHIVES)
	$(TESTCC) -o $@ $^ $(ARCHIVES)

test/css/test_css_parse: test/main.c test/css/css_parse.c $(ARCHIVES)
	$(TESTCC) -o $@ $^ $(ARCHIVES)

TESTS+=test/css/test_selector_parse
TESTS+=test/css/test_scalar_parse
TESTS+=test/css/test_css_parse
