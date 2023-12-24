#ifndef KUPIDINI_H
#define KUPIDINI_H

#include <stddef.h>


#define KUPIDINI_SIZE size_t

#define KUPIDINI_BOOL char
#define KUPIDINI_TRUE 1
#define KUPIDINI_FALSE 0

/* * * LEXER * * */
#define KUPIDINI_SPECIAL "=:[]"
#define KUPIDINI_LINE "\n\r"
#define KUPIDINI_WHITESPACE " \t"

/* * * PARSER * * */
/* By default, notating with colon is supported */
#define KUPIDINI_EQUALSIGN "=:"
#define KUPIDINI_START_SECTION "["
#define KUPIDINI_END_SECTION "]"

typedef struct {
	char *s;
	KUPIDINI_SIZE l;
} KupidiniSlice;

typedef struct {
	enum KupidiniLexed_Type {
		KupidiniLexed_Type_Special,
		KupidiniLexed_Type_Identifier,
		KupidiniLexed_Type_Newline

	} type;
	union {
		char c;
		KupidiniSlice s;
	} data;
} KupidiniLexed;

/* Give it a pointer to a string with at least the specified length */
/* The pointer is advanced to the next place symbol */
/* If the pointer is not advanced, it means the length is not sufficient and
you should try again (with more len) or that it's done lexing (check if it's
pointing to a null byte) */
/* The end of the file is denoted with a null byte */
/* The returned value "has the same lifetime" of the string argument. If you
need to destroy or mutate the string (buffering?), please copy the
KupidiniSlice if its an identifier */
KupidiniLexed kupidini_lex(char **, KUPIDINI_SIZE);

#endif

