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
	if (!self)
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


	if (len_new > len_old + 2 || len_new < len_old - 2)
		return VALID;

	int min_len = (len_new < len_old) ? len_new : len_old;
	for (int i = 0; i < min_len; i++)
	{
		if (old[i] != new[i])
			difok++;
	}
	
	int length_diff = (len_new > len_old) ? (len_new - len_old) : (len_old - len_new);
	difok += length_diff;

	return (difok > 2 ? VALID : INVALID_SIMILAR);
}

char *getLast(PasswordHistory *self)
{
	if (!self)
		return NULL;

	char *last = NULL;
	for (int i = 0; self->old_passwords[i]; i++)
		last = self->old_passwords[i];

	return (last);
}

char **getLastN(PasswordHistory *self, int *N)
{
	if (!self || *N <= 0)
		return NULL;

	int size = getSize(self);
	if (size < *N)
		*N = size;

	return &(self->old_passwords[size - *N]);
}

void add_new_password(PasswordHistory *self, char *password)
{
	if (!self || !password)
		return;

	int size = getSize(self);
	if (size < 3)
	{
		self->old_passwords[size] = password;
	}
	else
	{
		for (int i = 1; i < 3; i++)
		{
			self->old_passwords[i - 1] = self->old_passwords[i];
		}
		self->old_passwords[2] = password;
	}
	self->old_passwords[3] = NULL;
}