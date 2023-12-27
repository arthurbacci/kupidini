#ifndef KUPIDINI_H
#define KUPIDINI_H

/*
 *	NOTE: it may be fine to parse linebreaks as special characters
 */

#include <stddef.h>


#define KUPIDINI_SIZE size_t

#define KUPIDINI_BOOL char
#define KUPIDINI_TRUE 1
#define KUPIDINI_FALSE 0

/* * * LEXER * * */
#define KUPIDINI_SPECIAL "=:[].#;"
#define KUPIDINI_LINE "\n\r"
#define KUPIDINI_WHITESPACE " \t"
#define KUPIDINI_ESCAPE "\\"

/* * * PARSER * * */
/* By default, notating with colon is supported */
#define KUPIDINI_EQUALSIGN "=:"
#define KUPIDINI_START_SECTION "["
#define KUPIDINI_END_SECTION "]"
#define KUPIDINI_COMMENT "#;"


/* Give it a pointer to a string with at least the specified length */
/* The pointer is advanced to the next place symbol */
/* If the pointer is not advanced, it means the length is not sufficient and
you should try again (with more len) or that it's done lexing (check if it's
pointing to a null byte) */
/* The end of the file is denoted with a null byte */
char *kupidini_lex(char **, KUPIDINI_SIZE);
KUPIDINI_BOOL kupidini_is_inside(const char, const char *const);


typedef enum {
	/* No values set */
	KupidiniParsedType_FEEDMORE,
	/* No values set */
	KupidiniParsedType_ERROR,
	/* No values set */
	KupidiniParsedType_COMMENT,
	/* [ X ] => a = X */
	KupidiniParsedType_SECTION,
	/* X = Y => a = X; b = Y */
	KupidiniParsedType_KEYVALUE,
	/* X     => a = X */
	KupidiniParsedType_KEY
} KupidiniParsedType;

KupidiniParsedType kupidini_parse(
	char **, KUPIDINI_SIZE,
	char **a, KUPIDINI_SIZE *as,
	char **b, KUPIDINI_SIZE *bs
);



#endif

