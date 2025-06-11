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

	
    int oldPswNumber = 3;
    char **old_passwords = history->getLastN(history, &oldPswNumber);
    
    if (old_passwords) {
		for (int i = 0; i < oldPswNumber; i++) {
			if (checkSimilar((char*)new_pw, old_passwords[i]) == INVALID_SIMILAR) {
				return INVALID_SIMILAR;
            }
        }
    }
	if (flags[0] && flags[1] && flags[2] && flags[3] && flags[4])
		return VALID;
    
    return INVALID_WEAK;
}

int main()
{
    printf("Password History Validator Test\n");
    printf("===============================\n\n");

    // Create password history
    PasswordHistory history;
    
    // Initialize with some old passwords
    history.old_passwords = malloc(5 * sizeof(char*));
    history.old_passwords[0] = strdup("OldPass123@");
    history.old_passwords[1] = strdup("PrevPass456#");
    history.old_passwords[2] = strdup("LastPass789$");
    history.old_passwords[3] = strdup("CurrentPass1@");
    history.old_passwords[4] = NULL; // End marker
    
    // Set function pointers
    history.getLast = getLast;
    history.getLastN = getLastN;
    
    // Test cases
    struct {
        const char *new_pw;
        const char *description;
        PwStatus expected;
    } tests[] = {
        {"NewPassword123@", "Valid new password", VALID},
        {"password123@", "Missing uppercase", INVALID_WEAK},
        {"PASSWORD123@", "Missing lowercase", INVALID_WEAK},
        {"Password@", "Missing digit", INVALID_WEAK},
        {"Password123", "Missing special character", INVALID_WEAK},
        {"Pass1@", "Too short", INVALID_WEAK},
        {"CurrentPass1@", "Same as current password", INVALID_WEAK},
        {"OldPass123@", "Same as old password", INVALID_SIMILAR},
        {"PrevPass456#", "Same as previous password", INVALID_SIMILAR},
        {"LastPass789$", "Same as last password", INVALID_SIMILAR},
        {"OldPass124@", "Similar to old password (1 char diff)", INVALID_SIMILAR},
        {"PrevPass457#", "Similar to previous password (1 char diff)", INVALID_SIMILAR},
        {"CompletelyNew1@", "Valid - different from all history", VALID},
        {"", "Empty password", INVALID_WEAK},
        {"VeryDifferentPass1@", "Valid - completely different", VALID},
        {"CurrentPass2@", "Similar to current (1 char diff)", INVALID_SIMILAR},
    };
    
    int num_tests = sizeof(tests) / sizeof(tests[0]);
    int passed = 0;
    
    for (int i = 0; i < num_tests; i++) {
        printf("Test %d: %s\n", i + 1, tests[i].description);
        printf("New password: \"%s\"\n", tests[i].new_pw);
        
        PwStatus result = validate_password(tests[i].new_pw, &history);
        
        const char* result_str;
        switch(result) {
            case VALID: result_str = "VALID"; break;
            case INVALID_WEAK: result_str = "INVALID_WEAK"; break;
            case INVALID_SIMILAR: result_str = "INVALID_SIMILAR"; break;
            default: result_str = "UNKNOWN"; break;
        }
        
        const char* expected_str;
        switch(tests[i].expected) {
            case VALID: expected_str = "VALID"; break;
            case INVALID_WEAK: expected_str = "INVALID_WEAK"; break;
            case INVALID_SIMILAR: expected_str = "INVALID_SIMILAR"; break;
            default: expected_str = "UNKNOWN"; break;
        }
        
        printf("Result: %s\n", result_str);
        
        if (result == tests[i].expected) {
            printf("✓ PASS\n");
            passed++;
        } else {
            printf("✗ FAIL (Expected: %s)\n", expected_str);
        }
        
        printf("\n");
    }
    
    printf("Summary: %d/%d tests passed\n", passed, num_tests);
    
    // Test history functions
    printf("\n--- History Function Tests ---\n");
    printf("Current password: %s\n", history.getLast(&history));
    printf("History size: %d\n", getSize(&history));
    
    int n = 3;
    char **last_n = history.getLastN(&history, &n);
    printf("Last %d passwords:\n", n);
    for (int i = 0; i < n; i++) {
        printf("  %d: %s\n", i + 1, last_n[i]);
    }
    
    // Interactive test
    printf("\n--- Interactive Test ---\n");
    char new_password[100];
    
    printf("Enter new password to test: ");
    if (fgets(new_password, sizeof(new_password), stdin)) {
        // Remove newline if present
        int len = mystrlen(new_password);
        if (len > 0 && new_password[len - 1] == '\n') {
            new_password[len - 1] = '\0';
        }
        
        PwStatus result = validate_password(new_password, &history);
        
        switch(result) {
            case VALID:
                printf("✓ Password is VALID\n");
                break;
            case INVALID_WEAK:
                printf("✗ Password is INVALID_WEAK (missing requirements)\n");
                break;
            case INVALID_SIMILAR:
                printf("✗ Password is INVALID_SIMILAR (too similar to old passwords)\n");
                break;
        }
    }
    
    // Cleanup
    for (int i = 0; history.old_passwords[i]; i++) {
        free(history.old_passwords[i]);
    }
    free(history.old_passwords);
    
    return 0;
}