#include <stdio.h>
#include <kupidini.h>

#define OUTPUT_R(s) (output_r((s), sizeof(s)))

void output_r(char *s, KUPIDINI_SIZE l) {
	char *limit = s + l;

	char *before = NULL;
	KupidiniLexed le;
	for (;;) {
		le = kupidini_lex(&s, limit - s);

		if (le.type == KupidiniLexed_Type_Special) {
			printf("SPECIAL: %c\n", le.data.c);
		} else if (le.type == KupidiniLexed_Type_Newline) {
			printf("LINE: %d\n", le.data.c);
			if (!le.data.c) {
				break;
			}
		} else if (le.type == KupidiniLexed_Type_Identifier) {
			printf("ID: %.*s\n", (int)le.data.s.l, le.data.s.s);
		}
	}
}

void test1() {
	OUTPUT_R("[Section]\n\nwhen the = still sea\n\nwho? why!");
	printf("\n");
	OUTPUT_R("[Section]\n\nwhen the = still sea\n\nwho? why!\n\n\r\n");
}

int main() {
	test1();

	return 0;
}

