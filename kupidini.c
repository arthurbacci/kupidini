#include "kupidini.h"

KUPIDINI_BOOL kupidini_is_inside(const char c, const char *const s) {
	KUPIDINI_SIZE i;
	for (i = 0; s[i]; i++) if (c == s[i]) return KUPIDINI_TRUE;
	return KUPIDINI_FALSE;
}

char *kupidini_lex(char **ss, size_t l) {
	char *s;

	while (l != 0 && kupidini_is_inside(**ss, KUPIDINI_WHITESPACE)) {
		*ss += 1;
		l -= 1;
	}

	s = *ss;

	if ('\0' == *s) {
		return s;
	} else if (kupidini_is_inside(*s, KUPIDINI_SPECIAL)) {
		*ss += 1;
		return s;
	} else if (kupidini_is_inside(*s, KUPIDINI_LINE)) {
		for (;;) {
			*ss += 1;
			if (!kupidini_is_inside(**ss, KUPIDINI_LINE)) break;

			if (*ss - s >= l) {
				*ss = s;
				return NULL;
			}
		}
		if (**ss == '\0') return *ss;

		return s;
	} else {
		for (;;) {
			*ss += 1;

			if (
				!kupidini_is_inside(*(*ss-1), KUPIDINI_ESCAPE)
				&& (!**ss
				|| kupidini_is_inside(
					**ss, KUPIDINI_SPECIAL
					KUPIDINI_WHITESPACE KUPIDINI_LINE
				))
			) break;

			if (*ss - s >= l) {
				*ss = s;
				return NULL;
			}
		}
		return s;
	}
	
}


KupidiniParsedType kupidini_parse(
	char **ss, KUPIDINI_SIZE l,
	char **a, KUPIDINI_SIZE *as,
	char **b, KUPIDINI_SIZE *bs
) {
	char *lex, *fstlex;
	char *s = *ss;

	do {
		/* TODO: create a macro for this */
		lex = kupidini_lex(&s, l);
		if (lex == NULL) return KupidiniParsedType_FEEDMORE;
	} while (!(*lex) || kupidini_is_inside(*lex, KUPIDINI_LINE));

	fstlex = lex;
	
	if (kupidini_is_inside(*lex, KUPIDINI_START_SECTION)) {
		while (*lex) {
			lex = kupidini_lex(&s, l);
			if (lex == NULL) return KupidiniParsedType_FEEDMORE;
			
			if (kupidini_is_inside(*lex, KUPIDINI_END_SECTION)) {
				*a = fstlex + 1;
				*as = lex - *a;
				*ss = s;
				return KupidiniParsedType_SECTION;
			}
		}

		return KupidiniParsedType_ERROR;
	} else if (kupidini_is_inside(*lex, KUPIDINI_COMMENT)) {
		while (*lex && !kupidini_is_inside(*lex, KUPIDINI_LINE)) {
			lex = kupidini_lex(&s, l);
			if (lex == NULL) return KupidiniParsedType_FEEDMORE;
		}

		*ss = s;
		return KupidiniParsedType_COMMENT;
	} else if (!kupidini_is_inside(*lex, KUPIDINI_SPECIAL)) {
		char *keylex;
		
		while (!kupidini_is_inside(*lex, KUPIDINI_EQUALSIGN)) {
			lex = kupidini_lex(&s, l);
			if (lex == NULL) return KupidiniParsedType_FEEDMORE;

			if (*lex == '\0' || kupidini_is_inside(*lex, KUPIDINI_LINE)) {
				*a = fstlex;
				*as = lex - *a;
				*ss = s;
				return KupidiniParsedType_KEY;
			}
		}

		keylex = lex;

		for (;;) {
			lex = kupidini_lex(&s, l);
			if (lex == NULL) return KupidiniParsedType_FEEDMORE;

			if (*lex == '\0' || kupidini_is_inside(*lex, KUPIDINI_LINE)) {
				*a = fstlex;
				*as = keylex - *a;
				*b = keylex + 1;
				*bs = lex - *b;
				*ss = s;
				return KupidiniParsedType_KEYVALUE;
			}
		}
	}

	return KupidiniParsedType_ERROR;
}





