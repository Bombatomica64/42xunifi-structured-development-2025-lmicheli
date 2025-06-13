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
//@#$%^&*
static int isSpecialChar(char c)
{
	return (c == '@' || c == '#' || c == '$' || c == '%' || c == '^' || c == '&' || c == '*');
}

PwStatus validate_password(const char *new_pw, PasswordHistory *history)
{
	char *curr_pw = history->getLast(history);

	if (!new_pw || !history)
		return INVALID_WEAK;

	if (mystrlen(new_pw) < 8)
		return INVALID_WEAK;

	bool flags[5] = {false, false, false, false, false}; // [0]: uppercase, [1]: lowercase, [2]: digit, [3]: special char, [4]: different from current password

	// Check if passwords are different
	if (curr_pw)
	{
		if (mystrlen(new_pw) != mystrlen(curr_pw))
		{
			flags[4] = true; // Different length means different password
		}
		else
		{
			// Compare character by character
			for (int i = 0; new_pw[i] != '\0'; i++)
			{
				if (new_pw[i] != curr_pw[i])
				{
					flags[4] = true;
					break;
				}
			}
		}
	}
	else
	{
		flags[4] = true; // No current password, so it's different
	}

	// Check character requirements
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

	int oldPswNumber = 3;
	char **old_passwords = history->getLastN(history, &oldPswNumber);

	if (old_passwords)
	{
		for (int i = 0; i < oldPswNumber; i++)
		{
			if (checkSimilar((char *)new_pw, old_passwords[i]) == INVALID_SIMILAR)
			{
				return INVALID_SIMILAR;
			}
		}
	}
	if (flags[0] && flags[1] && flags[2] && flags[3] && flags[4])
	{
		history->add_new_password(history, (char *)new_pw);
		return VALID;
	}

	return INVALID_WEAK;
}
