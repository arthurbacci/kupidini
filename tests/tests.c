#include <stdio.h>
#include <kupidini.h>

#define OUTPUT_R(s) (output_r((s), sizeof(s)))

void output_r(char *s, KUPIDINI_SIZE l) {
	char *ss = s;
	char *limit = s + l;
	char *le;

	printf("\n");

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
	
	s = ss;
	printf("\n");

	do {
		char *a = NULL, *b = NULL;
		KUPIDINI_SIZE as = 0, bs = 0;
		KupidiniParsedType p = kupidini_parse(&s, limit - s, &a, &as, &b, &bs);
		
		printf("%d", p);
		if (p == KupidiniParsedType_KEY || p == KupidiniParsedType_SECTION)
			printf("\t%.*s\n", (int)as, a);
		else if (p == KupidiniParsedType_KEYVALUE)
			printf("\t%.*s\t%.*s\n", (int)as, a, (int)bs, b);
		else
			printf("\n");
		
		if (p == 0 || p == 1) break;
		
		

		/*if (kupidini_is_inside(*le, KUPIDINI_SPECIAL))
			printf("SPECIAL: %c\n", *le);
		else if (*le == '\0' || kupidini_is_inside(*le, KUPIDINI_LINE))
			printf("LINE: %d\n", *le);
		else
			printf("ID: %.*s\n", (int)(s - le), le);*/

	} while (*s != '\0');

	printf("\n");
}

void test1() {
	OUTPUT_R("[Section]\n\nwhen the = still sea\n\nwho? why!");
	OUTPUT_R("when the =\n\nwho? why!\n\n\r\n");
	OUTPUT_R("Sec\\]tion]\n\nwhen\\\n the === s\\\\till sea\n\nwho? why=");
}

int main() {
	test1();

	return 0;
}

