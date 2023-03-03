#include <fcntl.h>
#include <search.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFSIZE 1024 //Can use BUFSIZE in program as 1024

typedef struct {   //Function Structure Type
	char word[42]; //sets variable type
	unsigned count;  //type of int variable
} WORD_T;  //this is an array of words

WORD_T *words = NULL;  //global variable set to 0 
size_t total_words = 0; // total words set to 0
void print_and_free(WORD_T *words, size_t total_words, char *infile);

int comparator(const void *a, const void *b) {  //function named comparitor
	char *a_ptr = (char*) a;
	WORD_T *b_ptr = (WORD_T*) b;
	return strcmp(a_ptr, b_ptr-> word);
    }


int main(int argc, char **argv) {
	if (argc != 2) return -1; // if argc does not equal 2 return -1
	char *infile = argv[1];  //char infile pointer is set to argv[1] value
	int fd = open(infile, O_RDONLY); //opens file and is given name fd
	if (fd == -1) return -2; // if fd = -1, return -2
	char *buf = malloc(BUFSIZE * sizeof(char));  // allocates memory in the heap at pointer buf

	int n_char;
	while ((n_char = read (fd, buf, BUFSIZE - 1))>0){
		char *bufp = buf;  // creates pointer with current buf value
		char *token = strsep(&bufp, "\n"); //returns first value in bufp
		while (token != NULL){
			char *match;
			match = lfind(token, words, &total_words, sizeof(WORD_T), comparator);
			if (match == NULL){
				total_words ++;
				words = realloc(words,sizeof(WORD_T) * total_words +1);
				strcpy(words[total_words - 1].word, token);
				words[total_words - 1].count = 1;
			}
			else{
				words->count++;
			}
			token = strsep(&bufp, "\n");
			printf("\n%s", token);
		}
	}

	//WORD_T *result = lfind(token, words, &total_words, sizeof(WORD_T), comparator);
  
	//printf("%d\n", (*result).count);

	// TODO: repeatedly call `read()` into a buffer of
	//       size BUFSIZE. Split the text in the buffer
	//       on newlines and spaces. For each token:
	//       search the `words` array to see if that
	//       word has already been added and if so
	//       increment the count. Otherwise add a new
	//       WORD_T struct to the end of the array of
	//       structs `words` and set the fields accordingly.

	// TODO: its possible that a word is split between
	//       one fill of the buffer and the next. You must
	//       move the last word at the end of the buffer to
	//       the beginning of the buffer and then fill
	//       the buffer from that point!

	print_and_free(words, total_words, infile);
	close(fd);
	return 0;
}

void print_and_free(WORD_T *words, size_t total_words, char *infile) {
	int sum = 0;
	for (int i = 0; i < total_words; ++i) { //goes through each token in heap
		if (words[i].count > 1) //counts words
			printf("%s: %u\n", words[i].word, words[i].count);
		sum += words[i].count; //increases word count
	}
	printf("\n%d %s\n", sum, infile);
	printf("\n");
	free(words);}


