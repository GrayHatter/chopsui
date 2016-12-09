#include <stdint.h>
#include <stddef.h>
#include "util/unicode.h"

uint8_t masks[] = {
	0x80,
	0xE0,
	0xF0,
	0xF8,
	0xFC,
	0xFE
};

uint32_t utf8_decode(const char **s) {
	uint32_t cp = 0;
	if (**s < 0x80) {
		// shortcut
		cp = **s;
		++*s;
		return cp;
	}
	int size = utf8_size(*s);
	if (size == -1) {
		return UTF8_INVALID;
	}
	uint32_t c = (uint8_t)**s;
	++*s;
	c &= ~masks[size - 1];
	c <<= (size - 1) * 6;
	cp |= c;
	int shift = size * 6;
	while (--size) {
		uint32_t c = (uint8_t)**s;
		c &= ~0xC0;
		c <<= shift;
		shift -= 6;
		cp |= c;
		++*s;
	}
	return cp;
}
