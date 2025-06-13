#include "password_validator.h"

static int mystrlen(const char *str)
{
	int ret = 0;
	if (!str)
		return 0;
	while (str[ret] != '\0')
		ret++;
	return ret;
}

static int isUpper(char c)
{
	return (c >= 'A' && c <= 'Z');
}

static int isLower(char c)
{
	return (c >= 'a' && c <= 'z');
}

static int isDigit(char c)
{
	return (c >= '0' && c <= '9');
}

static int isSpecialChar(char c)
{
	return (c == '@' || c == '#' || c == '$' || c == '%' || c == '^' || c == '&' || c == '*');
}

static bool is_different_from_current(const char *new_pw, const char *curr_pw)
{
	if (!curr_pw)
		return true;

	if (mystrlen(new_pw) != mystrlen(curr_pw))
		return true;

	for (int i = 0; new_pw[i] != '\0'; i++)
	{
		if (new_pw[i] != curr_pw[i])
			return true;
	}
	return false;
}

static void check_character_requirements(const char *new_pw, bool *flags)
{
	for (int i = 0; new_pw[i] != '\0'; i++)
	{
		if (isUpper(new_pw[i]))
			flags[0] = true;
		else if (isLower(new_pw[i]))
			flags[1] = true;
		else if (isDigit(new_pw[i]))
			flags[2] = true;
		else if (isSpecialChar(new_pw[i]))
			flags[3] = true;
	}
}

static PwStatus check_similarity_with_history(const char *new_pw, PasswordHistory *history)
{
	int oldPswNumber = 3;
	char **old_passwords = history->getLastN(history, &oldPswNumber);

	if (!old_passwords)
		return VALID;

	for (int i = 0; i < oldPswNumber; i++)
	{
		if (checkSimilar(new_pw, old_passwords[i]) == INVALID_SIMILAR)
			return INVALID_SIMILAR;
	}
	return VALID;
}

static bool all_requirements_met(const bool flags[5])
{
	return flags[0] && flags[1] && flags[2] && flags[3] && flags[4];
}

PwStatus validate_password(const char *new_pw, PasswordHistory *history)
{
	if (!new_pw || !history)
		return INVALID_WEAK;

	if (mystrlen(new_pw) < 8)
		return INVALID_WEAK;

	const char *curr_pw = history->getLast(history);
	bool flags[5] = {false, false, false, false, false}; // flags for uppercase, lowercase, digit, special char, and different from current

	flags[4] = is_different_from_current(new_pw, curr_pw);

	check_character_requirements(new_pw, flags);

	// Check similarity with password history
	PwStatus similarity_status = check_similarity_with_history(new_pw, history);
	if (similarity_status == INVALID_SIMILAR)
		return INVALID_SIMILAR;

	if (all_requirements_met(flags))
	{
		history->add_new_password(history, new_pw);
		return VALID;
	}

	return INVALID_WEAK;
}