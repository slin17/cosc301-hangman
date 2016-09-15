#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>

void getastring (char **buf){
	printf("buf_pointer: %p\n", buf);
	printf ("buf: %s\n", *buf);
	*buf = NULL;
	char *s = (char *)malloc(sizeof(char)*128);
	if (fgets(s, 128, stdin) == NULL)
		return;
	*buf = s;
	printf ("str: %s\n", *buf);
}

int main(int argc, char **argv) {
	char *str = "blurgh";
	printf("str_pointer: %p\n", &str); 
	getastring(&str);
	printf("We got the string %s\n", str);
	return 0;
}
