#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>

char *removewhitespace (char *s) {
	char *returnval = malloc(sizeof(char)*(strlen(s)+1));
	int i;
	int copypos = 0;
	for (i=0; i< strlen(s); i++) {
		if (!isspace(s[i])){
			returnval[copypos] = s[i];
			copypos++;
		}
	}
	returnval[copypos] = '\0';
	return returnval;
}

int main() {
	char s[] = "i love you";
	char *arr = removewhitespace(s);
	printf("white space removed: %s\n", arr);
	free(arr); 
	return 0;
}
