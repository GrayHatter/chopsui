#include <stdlib.h>
#include "util/list.h"
#include "css.h"

void media_rule_free(struct media_rule *rule) {
	while (rule) {
		struct media_rule *next = rule->next;
		free(rule);
		rule = next;
	}
}
