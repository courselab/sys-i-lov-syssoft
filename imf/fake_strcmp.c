#include <string.h>

/*
 * redefining strcmp function to always return 0 (strings are equal)
 */

int strcmp(const char * str1, const char * str2){
	return 0;
}
