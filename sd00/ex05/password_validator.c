#include "password_validator.h"

static int mystrlen(const char *str)
{
    int ret = 0;
    if(!str)
        return 0;
    while(str[ret] != '\0')
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

PwStatus validate_password(const char *new_pw, const char *curr_pw)
{
	if(!new_pw || !curr_pw)
		return INVALID;

	if (mystrlen(new_pw) < 8 )
		return INVALID;
	
	bool flags[5] = {false, false, false, false, false}; // [0]: uppercase, [1]: lowercase, [2]: digit, [3]: special char, [4]: different from current password

	if (mystrlen(new_pw) != mystrlen(curr_pw))
		flags[4] = true; // Different length means different password
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
		else if (new_pw[i] != curr_pw[i])
			flags[4] = true;
	}

	if (flags[0] && flags[1] && flags[2] && flags[3] && flags[4])
		return VALID;

	return INVALID;
}
