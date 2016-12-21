test/parse/test_parse_selector: test/main.c test/parse/parse_selector.c $(ARCHIVES)
	$(TESTCC) -o $@ $^ $(ARCHIVES)

test/parse/test_parse_scalar: test/main.c test/parse/parse_scalar.c $(ARCHIVES)
	$(TESTCC) -o $@ $^ $(ARCHIVES)

TESTS+=test/parse/test_parse_selector
TESTS+=test/parse/test_parse_scalar
