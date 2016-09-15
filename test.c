#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>

int main() {
	FILE *fp = fopen("/usr/share/dict/words", "r");
	int num_words = 0;
	char word[128];
	while (fgets(word, 128, fp)!= NULL){
		fscanf(fp,"%s",word);
		int len = strlen(word);
		int c = 0;
		for (int i=0; i<len; i++) {
			word[i] = toupper(word[i]);
			if(isalpha(word[i])!=0){
				c++;
			}
		}
		if (c==len) {
			char* p = strchr(word,'\n');
			if (p) {
				*p ='\0';
			}
			num_words++;
			//strupr(word);
			printf("word: %s, len: %d\n",word,len);
		}
		
	}
	fclose(fp); 
	printf("num_words: %d\n", num_words); 
	return 0; 
}
