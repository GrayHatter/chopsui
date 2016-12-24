#include <stdlib.h>
#include "util/list.h"
#include "css.h"

void media_rule_free(media_rule_t *rule) {
	while (rule) {
		media_rule_t *next = rule->next;
		free(rule);
		rule = next;
	}
}
