#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>


/*
 * linked list data structure definitions
 */
struct _wordnode {
    char word[256];
    struct _wordnode *next;
};
typedef struct _wordnode wordnode;


/*
 * Be happy you didn't have to write this function.
 * Prints a low-tech ASCII gallows.  Max number of misses
 * is 7 (i.e., if there are 7 misses, the player loses and
 * the poor sap gets hung).  
 */
void print_gallows(int num_missed) {
    // make sure that we got called in a reasonable way
    assert(num_missed >= 0 && num_missed <= 7);

    printf("\n\n       |||========|||\n");
    if (num_missed > 0) {
        printf ("       |||         |\n");
    } else {
        printf ("       |||          \n");
    }

    if (num_missed > 1) {
        printf ("       |||         O\n");
    } else {
        printf ("       |||          \n");
    }

    if (num_missed > 2) {
        if (num_missed > 4) {
            printf ("       |||        /|\\\n");
        } else if (num_missed > 3) {
            printf ("       |||        /| \n");
        } else {
            printf ("       |||        /  \n");
        }
    } else {
        printf ("       |||           \n");
    }

    if (num_missed > 5) {
        if (num_missed > 6) {
            printf ("       |||        / \\\n");
        } else {
            printf ("       |||        /  \n");
        }
    } else {
        printf ("       |||           \n");
    }

    printf ("       |||\n");
    printf ("       |||\n");
    printf ("     =================\n\n");
}

void enter(char *letter);
void prompt(char *letter);
void display(char *success);

/*
 * Play one game of Hangperson.  The secret word is passed as a
 * parameter.  The function should return true if the player won,
 * and false otherwise.
 */
bool one_game(const char *word) 
{
	char letter[128]="";
	char used[128]="";
	char *success=malloc(sizeof(char)*(strlen(word)+1)); 
	//initiate using malloc to decide size based on a variable
	int len=strlen(word);
	for (int k=0;k<len;k++)
	{
		success[k]='_';
	}
	//initiate success with _
	success[len]='\0';
	//add null termination
	int wrong=0;
	int in =0;
	int suc=0;
	bool result=true;

	//printf("%s\n",used);
	//while not success and not fail
	while (wrong < 7 && suc < len) 
	{
		suc = 0; 
		printf("Missed:%d\n", wrong); 			//show the number missed
		print_gallows(wrong);
		printf("Letters already used: %s\n",used);	//show used letters
		display(success);				//show current state
		
		prompt(letter); 				//ask for input

		while(strstr(used,letter)!=NULL) 		//check if used
		{
			printf("You have already guessed that letter! Please try another one.\n");
			prompt(letter);
		}
		strcat(used,letter); 				//add to used if not

		for (int i=0; i<len; i++) 			//change 'success' if correct
		{
			if (*letter== word[i])
			{
				in = 1;	 
				success[i] = word[i]; 
				
			}
		}
		for (int j=0; j<strlen(success); j++) 		
		{
			if (success[j]!='_') 
			{
				suc++; 
			}
		}
		
		if (in != 1) 					//update wrong if not correct
		{
			wrong++;
			printf("Not so lucky this time. \n");
		}
		else
		{
			printf("You got lucky with that guess!\n");
		}
		in = 0;
	}
	//after last guess
	
	printf("Missed:%d\n", wrong); 
	print_gallows(wrong);
	printf("Letters already used: %s\n",used);
	if (suc == len) 
	{
		printf("You've won!\n"); 
		result=true;
	}
	else 
	{
		printf("Sorry, the secret word is: %s\n", word);
		result=false;
	}
	free(success); 
	return result;
}


//function that displays current state by using correctly guessed letter and '_'
void display( char *success)
{	
	int len= strlen(success);
	for (int i=0;i<len;i++) 		//print letter or _ according to successful guess
	{
		if (success[i]!='_')
		{
			printf("%c ",success[i]);
		}
		else 
		{
			printf("_ ");
		}
	}
	printf("\n");
	//printf("%s\n", success);
}

//function that calls enter() and checks if input is in desired format
void prompt(char *letter)
{	
	bool isletter=false;
	bool alpha=true;
	while (!isletter)
	{
		enter(letter);
		int len=strlen(letter);
		for (int i=0;i<len;i++)			//test if there is non-alphabet char
		{
			alpha=true;
			if (!isalpha(letter[i]))
			{
				alpha=false;
				continue;
			}
		}
		
		if (strlen(letter)==1 && alpha==true)		//test if is alphabet & one single char
		{
			isletter=true;
			letter[0]=toupper(letter[0]);
		}
		else if (alpha==false)				//print instructions accordingly
		{
			printf("Enter a letter please. Nothing else.\n");
		}
		else 
		{
			printf("Enter one and only one letter. \n");
		}
	}
}


//function that asks for an input
void enter(char *letter)
{
	
    	printf("What is your guess? ");				
    	fgets(letter, 128, stdin);
	char* p = strchr(letter,'\n');//to strip of the newline character
	if (p) 
	{
		*p ='\0';
	}
	
}

/* 
 * wordbank-related functions. please don't change the
 * function prototypes for these three functions.
 * load_words takes the name of the file that should be
 * opened and words read from, and a pointer to an int
 * that should be indirectly modified to store the number
 * of words loaded from the file.  The function should 
 * return the linked list of words.
 */
wordnode *load_words(const char *filename, int *num_words) 
{
	FILE *fl;	
	char str[256];
	fl=fopen(filename,"r");
	*num_words=0;
	struct _wordnode *head=NULL;
	while (fgets(str,256,fl)!=NULL)
	{
		fscanf(fl,"%s",str);  			//input words
		int len = strlen(str);
		int c = 0;
		for (int i=0; i<len; i++) 
		{
			str[i] = toupper(str[i]);
			if(isalpha(str[i])!=0)
			{
				c++;
			}
		}
		if (c==len)
		{
			char* p = strchr(str,'\n');     //to strip of the newline character
			if (p) 
			{
				*p ='\0';
			}
			*num_words=*num_words+1;	
			if (head!=NULL)			//creat linked list
          		{
				struct _wordnode *current=head;
				struct _wordnode *new=(struct _wordnode *)malloc(sizeof(struct _wordnode));
            			new->next=current;
      				strcpy((new->word),str);
				//printf("%s\n",(end->word));
				current=new;
				head=new;
				//printf("%s\n",(end->word));
				
			 }
       			 else
       			 {
       				head=(struct _wordnode *)malloc(sizeof(struct _wordnode));
			 	strcpy((head->word),str);
				head->next=NULL;
      			 }
		}
		
	}
	//head=new;
	//printf("%d\n",*num_words);
	fclose(fl);
	return head;
}

/*
 * Completely free and deallocate the linked list of words.
 */
void free_words(wordnode *wordlist) {
	
    struct _wordnode *current=wordlist;
    while (current!=NULL)
    {
        wordlist=wordlist->next;
        free(current);
        current=wordlist;
    }
    wordlist=current=NULL;//set pointer to null after free.

}

/*
 * Choose one random word from the linked list and return it.
 */
const char *choose_random_word(wordnode *wordlist, int num_words) {
	int num=rand();
	int run= num% num_words;	//run=random_number mod num_words
	struct _wordnode *head=wordlist;
	//printf("%d\n",num_words);
	while (run!=0)			//"walk" a special number of times to get a random word
	{
		head=head->next;
		run--;
	}
	//printf("%s\n",head->word);
	return head->word;
}


/*
 * The main function is where everything starts.  Choose a random
 * word and call one_game.  Start first on getting the word-loading
 * to work correctly, then handle the game playing capabilities.
 */
#ifndef AUTOTEST
int main() {
    srandom(time(NULL));
    int num_words = 0;
    wordnode *words = load_words("/usr/share/dict/words", &num_words);
    if (num_words == 0) {
        printf("Didn't load any words?!\n");
        return 0;
    }
    char *word = choose_random_word(words, num_words);
    one_game(word);
    free_words(words);
    return 0;
}
#endif
