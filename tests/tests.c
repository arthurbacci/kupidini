#include <stdio.h>
#include <kupidini.h>

#define OUTPUT_R(s) (output_r((s), sizeof(s)))

void output_r(char *s, KUPIDINI_SIZE l) {
	char *limit = s + l;
	char *le;

	do {
		le = kupidini_lex(&s, limit - s);

		if (le == NULL) {
			fprintf(stderr, "le is null in tests\n");
			return;
		}
		

		if (kupidini_is_inside(*le, KUPIDINI_SPECIAL))
			printf("SPECIAL: %c\n", *le);
		else if (*le == '\0' || kupidini_is_inside(*le, KUPIDINI_LINE))
			printf("LINE: %d\n", *le);
		else
			printf("ID: %.*s\n", (int)(s - le), le);

	} while (*le != '\0');
}

void test1() {
	OUTPUT_R("[Section]\n\nwhen the = still sea\n\nwho? why!");
	printf("\n");
	OUTPUT_R("[[Section]]\n\nwhen the === still sea\n\nwho? why!\n\n\r\n");
}

int main() {
	test1();

	return 0;
}

