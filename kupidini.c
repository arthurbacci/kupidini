#include "kupidini.h"

KUPIDINI_BOOL is_inside(const char c, const char *const s) {
	KUPIDINI_SIZE i;
	for (i = 0; s[i]; i++) if (c == s[i]) return KUPIDINI_TRUE;
	return KUPIDINI_FALSE;
}

KupidiniLexed kupidini_lex(char **ss, size_t l) {
	char *s;

	while (l != 0 && is_inside(**ss, KUPIDINI_WHITESPACE)) {
		*ss += 1;
		l -= 1;
	}

	s = *ss;

	if ('\0' == *s) {
		KupidiniLexed r = {KupidiniLexed_Type_Newline, {'\0'}};
		return r;
	} else if (is_inside(*s, KUPIDINI_SPECIAL)) {
		KupidiniLexed r = {KupidiniLexed_Type_Special};
		r.data.c = *s;

		*ss += 1;
		return r;
	} else if (is_inside(*s, KUPIDINI_LINE)) {
		KupidiniLexed r = {KupidiniLexed_Type_Newline, {'\n'}};
		for (;;) {
			*ss += 1;
			if (!is_inside(**ss, KUPIDINI_LINE)) break;

			if (*ss - s >= l) {
				*ss = s;
				return r;
			}
		}

		if ('\0' == **ss) r.data.c = '\0';
		return r;
	} else {
		KupidiniLexed r = {KupidiniLexed_Type_Identifier};
		KupidiniSlice slice;

		for (;;) {
			*ss += 1;

			if (!**ss || is_inside(**ss, KUPIDINI_SPECIAL" "KUPIDINI_LINE)) break;

			if (*ss - s >= l) {
				*ss = s;
				return r;
			}
		}
		slice.s = s;
		slice.l = *ss - s;
		r.data.s = slice;
		return r;
	}
	
}







