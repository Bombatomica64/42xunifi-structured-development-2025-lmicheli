#ifndef PASSWORD_VALIDATOR_H
#define PASSWORD_VALIDATOR_H

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum
{
	VALID = 0,
	INVALID_WEAK = 1,
	INVALID_SIMILAR = 2,
} PwStatus;

typedef struct PasswordHistory
{
	char **old_passwords;

	char *(*getLast)(struct PasswordHistory *self);
	int (*getSize)(struct PasswordHistory *self);
	char **(*getLastN)(struct PasswordHistory *self, int *N);
	// void (*add_old_password)(struct PasswordHistory *self, const char *password);
} PasswordHistory;

PwStatus checkSimilar(char *new, char *old);
int getSize(PasswordHistory *self);
char *getLast(PasswordHistory *self);
char **getLastN(PasswordHistory *self, int *N);

PwStatus validate_password(const char *new_pw, PasswordHistory *history);
#endif // PASSWORD_VALIDATOR_H