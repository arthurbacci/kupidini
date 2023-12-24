#include "kupidini.h"

KUPIDINI_BOOL is_inside(const char c, const char *const s) {
	KUPIDINI_SIZE i;
	for (i = 0; s[i]; i++) if (c == s[i]) return KUPIDINI_TRUE;
	return KUPIDINI_FALSE;
}

KupidiniLexed kupidini_lex(char **ss, size_t l) {
	char *s = *ss;
	KUPIDINI_SIZE i = 0;

	if ('\0' == s[i]) {
		KupidiniLexed r = {KupidiniLexed_Type_Newline, {'\0'}};
		return r;
	} else if (is_inside(s[i], KUPIDINI_SPECIAL)) {
		KupidiniLexed r = {KupidiniLexed_Type_Special};
		r.data.c = s[i];

		*ss += 1;
		return r;
	} else if (is_inside(s[i], KUPIDINI_LINE)) {
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

			if (!**ss || is_inside(**ss, KUPIDINI_SPECIAL KUPIDINI_LINE)) break;

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







