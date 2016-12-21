test/parse/test_selector_parse: test/main.c test/parse/selector_parse.c $(ARCHIVES)
	$(TESTCC) -o $@ $^ $(ARCHIVES)

test/parse/test_scalar_parse: test/main.c test/parse/scalar_parse.c $(ARCHIVES)
	$(TESTCC) -o $@ $^ $(ARCHIVES)

test/parse/test_stylesheet_parsec: test/main.c test/parse/stylesheet_parsec.c $(ARCHIVES)
	$(TESTCC) -o $@ $^ $(ARCHIVES)

TESTS+=test/parse/test_selector_parse
TESTS+=test/parse/test_scalar_parse
TESTS+=test/parse/test_stylesheet_parsec
