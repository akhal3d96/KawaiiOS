#include <stdint.h>
#include <string.h>

/* Copy len bytes from src to dest.*/
void memcpy(void *dest, const void *src, uint32_t len)
{
	const uint8_t *sp = (const uint8_t *)src;
	uint8_t *dp = (uint8_t *) dest;
	for (; len != 0; len--)
		*dp++ = *sp++;
}

/* Write len copies of val into dest.*/
void memset(void *dest, uint8_t val, uint32_t len)
{
	uint8_t *temp = (uint8_t *) dest;
	for (; len != 0; len--)
		*temp++ = val;
}

/* Compare two strings. Should return -1 if */
/* str1 < str2, 0 if they are equal or 1 otherwise.*/
int strcmp(char *str1, char *str2)
{
	int i = 0;
	int failed = 0;
	while (str1[i] != '\0' && str2[i] != '\0') {
		if (str1[i] != str2[i]) {
			failed = 1;
			break;
		}
		i++;
	}
	/* why did the loop exit? */
	if ((str1[i] == '\0' && str2[i] != '\0')
	    || (str1[i] != '\0' && str2[i] == '\0'))
		failed = 1;

	return failed;
}

/* Copy the NULL-terminated string src into dest, and*/
/* return dest.*/
char *strcpy(char *dest, const char *src)
{
	do {
		*dest++ = *src++;
	}
	while (*src != 0);
}

/* Concatenate the NULL-terminated string src onto*/
/* the end of dest, and return dest.*/
char *strcat(char *dest, const char *src)
{
	while (*dest != 0) {
		*dest = *dest++;
	}

	do {
		*dest++ = *src++;
	}
	while (*src != 0);
	return dest;
}
