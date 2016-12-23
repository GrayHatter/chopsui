test/parse/test_selector_parse: test/main.c test/parse/selector_parse.c $(ARCHIVES)
	$(TESTCC) -o $@ $^ $(ARCHIVES)

test/parse/test_scalar_parse: test/main.c test/parse/scalar_parse.c $(ARCHIVES)
	$(TESTCC) -o $@ $^ $(ARCHIVES)

test/parse/test_stylesheet_parse: test/main.c test/parse/stylesheet_parse.c $(ARCHIVES)
	$(TESTCC) -o $@ $^ $(ARCHIVES)

TESTS+=test/parse/test_selector_parse
TESTS+=test/parse/test_scalar_parse
TESTS+=test/parse/test_stylesheet_parse
