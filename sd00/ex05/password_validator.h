#ifndef PASSWORD_VALIDATOR_H
#define PASSWORD_VALIDATOR_H

#include <stdbool.h>
#include <string.h>
#include <stdio.h>

typedef enum {
	VALID = 0,
	INVALID = 1,
	EMPTY,
	TOO_SHORT,
	TOO_LONG,
	NO_UPPERCASE,
	NO_LOWERCASE,
	NO_DIGIT,
	NO_SPECIAL_CHAR,
	NO_WHITESPACE,
} PwStatus;

PwStatus validate_password(const char *new_pw, const char *curr_pw);

#endif // PASSWORD_VALIDATOR_H