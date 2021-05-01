#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
#include<ctype.h>

#define ALPHABET_SIZE 26  // Alphabet size
#define MAX_WORD_SIZE 50    //assume all the word are no more than 50 characters

int nodeCount = 0; //variable to hold node count

typedef struct trienode
{
    struct trienode *children[ALPHABET_SIZE];
    char character;
    bool endOfWord;     // isEndOfWord is true if the node represents end of a word 
}TrieNode;

//function to calculate index
int calcCharIndex(char c);
// returns new trie node (initialized to NULLs) 
TrieNode* createNode();
//insert word into trie
void insertWord(TrieNode *rootNode,char *word);
//function to store dictionary
TrieNode* storeDict(char* fileName);
//function to search given node
TrieNode* searchNode(TrieNode* rootNode,char* word);
//function to print suggested words
void printSuggetions(TrieNode* suggestedNode,char word_buffer[],int buffer_size);

int main(int argc, char *argv[])
{
    //exit program when enough arguments are not given
    if (argc!=2) {
        printf("Usage: %s <filename.txt>\n",argv[0]);
        return 0;
    }    
    
    TrieNode* rootNode = storeDict(argv[1]); 
   
    char partialWord[MAX_WORD_SIZE];  //hold input partial word
    printf("Memory space usage: %lu bytes\n",sizeof(*(rootNode))*nodeCount);

    while(1)
    {
        printf("Enter partial word for suggestions: ");
        scanf("%s",partialWord);
        TrieNode* suggestedNode = searchNode(rootNode,partialWord);
        printf("\n");
        if(suggestedNode != NULL){
            clock_t begin = clock();
            printSuggetions(suggestedNode,partialWord,strlen(partialWord));
            clock_t end = clock();
            double timeTaken = (double)(end-begin)/CLOCKS_PER_SEC;
            printf("\n");
            printf("Time taken to give suggestions: %f s\n",timeTaken);
            printf("\n");
        }else{
            printf("No Suggestions\n");
        }
  
    }
    return 0;
}

//function to calculate index
int calcCharIndex(char c)
{ 
   if((int)c >= 65 && (int)c <= 90){
    return tolower(c)-'a';  //convert upper case char to lower
   }else if( (int)c >= 97 && (int)c <= 122){
    return c-'a';
   }else
    return -1;     //return -1 for non alphabetic chars
}

// returns new trie node (initialized to NULLs) 
TrieNode* createNode()
{
    TrieNode* newTrieNode = (TrieNode*)malloc(sizeof(TrieNode));
    newTrieNode->character ='*';
    newTrieNode->endOfWord = false;
    int i;
    for (i = 0; i<ALPHABET_SIZE; i++)
    {
    	newTrieNode->children[i] = NULL;
    }
    return newTrieNode;
}

//insert word into trie
void insertWord(TrieNode *rootNode,char *word)
{
    int i,charIndex;
    TrieNode* newNode = rootNode;
    for(i=0;i<strlen(word)-1;i++)
    {
        charIndex = calcCharIndex(word[i]);
        if(charIndex >= 0){     //remove all non alphabetic chars
            if(newNode->children[charIndex] == NULL)
            {
                newNode->children[charIndex] = createNode();
                newNode->children[charIndex]->character = word[i];

            }
            newNode = newNode->children[charIndex];
        }
    }
    newNode->endOfWord = true;  // mark last node as leaf 
    nodeCount = nodeCount+1;
}

//function to store dictionary
TrieNode* storeDict(char* fileName)
{
    char word[MAX_WORD_SIZE];  
    int wordSize = MAX_WORD_SIZE;
    FILE *file = fopen(fileName,"r");
    if (file == NULL)
    {
        printf("Error: Can not open the file");
        exit(1);
    }
    TrieNode* rootNode = createNode();
    rootNode->character = '/';
    clock_t begin = clock();
    while(1)
    {
        fgets(word,wordSize,file);
        insertWord(rootNode,word);
        if(feof(file))        //tests the end-of-file indicator 
            break;
    }
    clock_t end = clock();
    double timeTaken = (double)(end-begin)/CLOCKS_PER_SEC;
    printf("Time taken to store dictionary: %.8lf s\n",timeTaken);
    fclose(file);
    return rootNode;
}

//function to search given node
TrieNode* searchNode(TrieNode* rootNode,char* word)
{
    int i,charIndex;
    TrieNode* currentNode = rootNode;
    for(i=0;i<strlen(word);i++)
    {
        charIndex = calcCharIndex(word[i]);
        if(currentNode != NULL)
          currentNode =currentNode->children[charIndex];
    }
    return currentNode;
}

//function to print suggested words
void printSuggetions(TrieNode* suggestedNode,char word_buffer[],int buffer_size)
{
    int i,charIndex;
    if(suggestedNode->endOfWord)
    {
        for(i=0;i<buffer_size;i++)
        {
            printf("%c",word_buffer[i]);
        }
        printf("\n");
    }
    for(i=0;i<ALPHABET_SIZE;i++)
    {
        if(suggestedNode->children[i]!=NULL)
        {
            word_buffer[buffer_size] = suggestedNode->children[i]->character;
            printSuggetions(suggestedNode->children[i],word_buffer,buffer_size+1);
        }
    }
}