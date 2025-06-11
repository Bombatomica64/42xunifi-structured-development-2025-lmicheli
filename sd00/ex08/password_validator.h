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
	char *old_passwords[4];

	char *(*getLast)(struct PasswordHistory *self);
	int (*getSize)(struct PasswordHistory *self);
	char **(*getLastN)(struct PasswordHistory *self, int *N);
	void (*add_new_password)(struct PasswordHistory *self, char *password);
	// void (*add_old_password)(struct PasswordHistory *self, const char *password);
} PasswordHistory;

PwStatus checkSimilar(char *new, char *old);
int getSize(PasswordHistory *self);
char *getLast(PasswordHistory *self);
char **getLastN(PasswordHistory *self, int *N);
void add_new_password(PasswordHistory *self, char *password);

PwStatus validate_password(const char *new_pw, PasswordHistory *history);


// ANSI color codes
#define COLOR_RESET   "\033[0m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_RED     "\033[31m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_BLUE    "\033[34m"
#define COLOR_CYAN    "\033[36m"


#endif // PASSWORD_VALIDATOR_H