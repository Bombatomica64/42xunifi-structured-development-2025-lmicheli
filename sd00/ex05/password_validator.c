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

int main() {
    printf("Password Validator Test\n");
    printf("======================\n\n");
    
    // Test cases
    struct {
        const char *new_pw;
        const char *curr_pw;
        const char *description;
    } tests[] = {
        {"Password123@", "oldpass", "Valid password - all requirements met"},
        {"password123@", "oldpass", "Missing uppercase"},
        {"PASSWORD123@", "oldpass", "Missing lowercase"},
        {"Password@", "oldpass", "Missing digit"},
        {"Password123", "oldpass", "Missing special character"},
        {"Pass13@", "oldpass", "Too short (7 chars)"},
        {"Password123@", "Password123@", "Same as current password"},
        {"MyNewP@ss1", "oldpassword", "Valid - different from current"},
        {"", "oldpass", "Empty new password"},
        {"ValidPass1@", "", "Empty current password"},
        {"Abc123@#", "different", "Valid - minimum requirements"},
        {"VeryLongPassword123@#$", "short", "Valid - long password"},
        {"NoSpecial123", "oldpass", "Missing special character"},
        {"password", "oldpass", "Missing uppercase, digit, special char"},
    };
    
    int num_tests = sizeof(tests) / sizeof(tests[0]);
    int passed = 0;
    
    for (int i = 0; i < num_tests; i++) {
        printf("Test %d: %s\n", i + 1, tests[i].description);
        printf("New password: \"%s\"\n", tests[i].new_pw);
        printf("Current password: \"%s\"\n", tests[i].curr_pw);
        
        PwStatus result = validate_password(tests[i].new_pw, tests[i].curr_pw);
        
        printf("Result: %s\n", result == VALID ? "VALID" : "INVALID");
        
        // Expected results (you can modify these based on your requirements)
        bool expected_valid = (i == 0 || i == 7 || i == 10 || i == 11);
        
        if ((result == VALID) == expected_valid) {
            printf("✓ PASS\n");
            passed++;
        } else {
            printf("✗ FAIL (Expected: %s)\n", expected_valid ? "VALID" : "INVALID");
        }
        
        printf("\n");
    }
    
    printf("Summary: %d/%d tests passed\n", passed, num_tests);
    
    // Interactive test
    printf("\n--- Interactive Test ---\n");
    char new_password[100];
    char current_password[100];
    
    printf("Enter new password: ");
    if (fgets(new_password, sizeof(new_password), stdin)) {
        // Remove newline if present
        int len = mystrlen(new_password);
        if (len > 0 && new_password[len-2] == '\n') {
            new_password[len-2] = '\0';
        }
        
        printf("Enter current password: ");
        if (fgets(current_password, sizeof(current_password), stdin)) {
            len = mystrlen(current_password);
            if (len > 0 && current_password[len-2] == '\n') {
                current_password[len-2] = '\0';
            }
            
            PwStatus result = validate_password(new_password, current_password);
            printf("Password validation result: %s\n", 
                   result == VALID ? "VALID" : "INVALID");
        }
    }
    
    return 0;
}