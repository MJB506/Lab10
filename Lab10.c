#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{	
    int count;
    struct Trie *children[26];
};

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie* dictionary = malloc(sizeof(struct Trie));
    dictionary->count = 0;

    int i;
    for (i=0; i<26; i++)
        dictionary->children[i] = NULL;

    return dictionary;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    int nextIndex;
    for(int i = 0; i < strlen(word); i++){
        nextIndex = word[i] - 'a';

        if(pTrie->children[nextIndex] == NULL){
            pTrie->children[nextIndex] = createTrie();
        }
        pTrie = pTrie->children[nextIndex];  
    }
    pTrie->count++;
    return;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    int nextIndex;
    for(int i = 0; i < strlen(word); i++){
        nextIndex = word[i] - 'a';
        if (pTrie->children[nextIndex] == NULL) {
            return 0;
        }
        pTrie = pTrie->children[nextIndex];
    }
    return pTrie->count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    for(int i = 0; i < 26; i++){
        if(pTrie->children[i] != NULL){
            deallocateTrie(pTrie->children[i]);
        }
        
    }
    free(pTrie);
    return NULL;
}



// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE *file = fopen(filename, "r");
    int numOfWords;
    fscanf(file, "%d", &numOfWords);
    

    for(int i = 0; i < numOfWords; i++){
        pInWords[i] = malloc(256 * sizeof(char)); 
        fscanf(file, "%s", pInWords[i]);
    }

    fclose(file);
    return numOfWords;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}