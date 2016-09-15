#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>

char *rstrip (char *str) {
	int len = strlen(str);
	char *re = malloc(sizeof(char)*(strlen(str)+1));
	int i;
	for (i=0; i<=len; i++) {
		re[i] = str[i];
	}
	i = len-1;
	while (isspace(re[i])) {
		re[i] = '\0';
		i--; 
	}
	return re;
}

int main() {
	char s[] = "iloveyou    ";
	printf("white space not yet stripped: %s, len: %d\n", s, strlen(s));
	char *arr = rstrip(s);
	printf("white space stripped: %s, len: %d\n", arr, strlen(arr));
	free(arr); 
	return 0;
}
