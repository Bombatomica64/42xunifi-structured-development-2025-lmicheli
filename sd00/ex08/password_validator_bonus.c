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

int getSize(PasswordHistory *self)
{
	if (!self || !self->old_passwords)
		return 0;
	int size = 0;
	for (int i = 0; self->old_passwords[i]; i++)
		size++;
	return size;
}

PwStatus checkSimilar(char *new, char *old)
{
	if (!new || !old)
		return VALID;

	int difok = 0;
	int len_new = mystrlen(new);
	int len_old = mystrlen(old);
	if (len_new > len_old + 2 || len_new > len_old - 2)
		return VALID;
	for (int i = 0; i < len_new && i < len_old; i++)
	{
		if (old[i] != new[i])
			difok++;
	}
	return ((len_new != len_old ? difok + 1 : difok) > 2 ? VALID : INVALID_SIMILAR);
}

char *getLast(PasswordHistory *self)
{
	if (!self || !self->old_passwords)
		return NULL;

	char *last;
	for (int i = 0; self->old_passwords[i]; i++)
		last = self->old_passwords[i];

	return (last);
}

char **getLastN(PasswordHistory *self, int *N)
{
	if (!self || !self->old_passwords || *N <= 0)
		return NULL;

	int size = getSize(self);
	if (size < *N)
		*N = size;

	return &(self->old_passwords[size - *N]);
}
