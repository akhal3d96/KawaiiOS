#include <stdint.h>

#define NULL (void *)0

void memcpy(void *dest, const void *src, uint32_t len);
void memset(void *dest, uint8_t val, uint32_t len);

char * strcpy(char *dest, const char *src);
char * strcat(char *dest, const char *src);

int strcmp(char *str1, char *str2);