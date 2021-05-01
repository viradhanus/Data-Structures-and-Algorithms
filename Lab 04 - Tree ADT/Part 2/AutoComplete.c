#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
#include<ctype.h>

#define ALPHABET_SIZE 26 // Alphabet size
#define MAX_WORD_SIZE 50    //assume all the word are no more than 50 characters

int nodeCount = 0;    //variable to hold node count

typedef struct lnkdStr
{
	char data;
	struct lnkdStr *next;
}lnkdStr;

typedef struct trienode
{
    struct trienode* children[ALPHABET_SIZE];
    lnkdStr* lnkdStr;
    bool endOfWord;
}TrieNode;


//function to calculate index
int calcCharIndex(char c);

//function to string => char
int strToChr(lnkdStr* begin,char* str,int initial);

lnkdStr* createString(char newData);
// returns new trie node (initialized to NULLs) 
TrieNode* createNode();

lnkdStr* linkedStrAppnd(char* str,int inital,int end);

TrieNode* linkedStrBrk(TrieNode* previousNode,TrieNode* node,lnkdStr* breakPossition);

void insertNode(TrieNode* rootNode,char* word);
//function to search given node
TrieNode* searchNodes(TrieNode* rootNode,char* word);
//function to store dictionary
TrieNode* storeDict(char* fileName);
//function to print suggested words
void printSuggetions(TrieNode* suggestedNode,char word_buffer[],int buffer_size);

int main(int argc, char *argv[])
{
    //exit program when enough arguments are not given
    if (argc!=2) {
        printf("Usage: %s <filename.txt>\n",argv[0]);
        return 0;
    }    
    
    TrieNode* rootNode = storeDict(argv[1]);   //change this for different files
    
    char partialWord[MAX_WORD_SIZE];  //hold input partial word
    printf("Memory space usage: %lu bytes\n",sizeof(*(rootNode))*nodeCount);

    while(1)
    {
        printf("Enter partial word for suggestions: ");
        scanf("%s",partialWord);
        TrieNode* suggestedNode = searchNodes(rootNode,partialWord);
        printf("\n");
        if(suggestedNode != NULL){

            clock_t begin = clock();
            printSuggetions(suggestedNode,partialWord,strlen(partialWord));
            clock_t end = clock();
            double timeTaken = (double)(end-begin)/CLOCKS_PER_SEC;
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
     return tolower(c)-'a';  
   }else if( (int)c >= 97 && (int)c <= 122){
     return c-'a';
   }else
     return -1;
}

//function to string => char
int strToChr(lnkdStr* begin,char* str,int initial)
{
    int newSize = initial;
    lnkdStr* newData = begin;

    while (newData != NULL)
    {
        str[newSize] = newData->data;
        newSize++;
        newData = newData->next;
    }
    str[newSize] = '\0';
    return newSize-1;
}

lnkdStr* createString(char newData)
{
    lnkdStr* newString = (lnkdStr*) malloc(sizeof(lnkdStr));
    newString -> data = newData;
    newString -> next = NULL;
    return newString;
}
// returns new trie node (initialized to NULLs) 
TrieNode* createNode()
{
    TrieNode* newtrieNode = (TrieNode*)malloc(sizeof(TrieNode));
    newtrieNode->lnkdStr = NULL;
    newtrieNode->endOfWord = false;
    int i;
    for (i=0;i<ALPHABET_SIZE;i++)
    {
    	newtrieNode->children[i] = NULL;
    }
    return newtrieNode;
}

lnkdStr* linkedStrAppnd(char* str,int inital,int end)
{
    int i;
    lnkdStr* current = createString(str[inital]);
    lnkdStr* newString = NULL;
    lnkdStr* string = current;

    for(i=inital+1;i<end;i++)
    {
        newString = createString(str[i]);
        current->next = newString;
        current = current->next;
    }
    current = NULL;
    return string;
}

TrieNode* linkedStrBrk(TrieNode* previousNode,TrieNode* node,lnkdStr* breakPossition)
{
    TrieNode* newNode = createNode();
    lnkdStr* newString = breakPossition->next;
    breakPossition->next = NULL;
    int index1 = calcCharIndex(newString->data);

    newNode->lnkdStr = node->lnkdStr;
    node->lnkdStr = newString;
    newNode->children[index1] = node;

    int index2 = calcCharIndex(newNode->lnkdStr->data);
    previousNode->children[index2] = newNode;

    return newNode;
}

void insertNode(TrieNode* rootNode,char* word)
{
    int lastLetterIndex = strlen(word)-1;
    int i=0,charIndex;

    TrieNode* currentNode = rootNode, *previousNode = NULL;
    TrieNode* newNode = NULL;
    lnkdStr* newData, *previousLetter = NULL;
    newData = currentNode->lnkdStr;
    while(i<=lastLetterIndex)
    {
    	charIndex = calcCharIndex(word[i]);
        if(charIndex >= 0){
    	    if(newData == NULL)
            {
    		if(currentNode->children[charIndex] == NULL)
    		{
    			newNode = createNode();
    			newNode->lnkdStr = linkedStrAppnd(word,i,lastLetterIndex);
                newNode->endOfWord = true;
    			currentNode->children[charIndex] = newNode;
    			nodeCount = nodeCount+1;
    			break;
    		}else
            {
                previousNode = currentNode;
                currentNode = currentNode->children[charIndex];
                previousLetter = currentNode->lnkdStr;
    			newData = currentNode->lnkdStr->next;
    		}
    	    }else
            {
    		if (newData->data != word[i])
    		{
    			currentNode = linkedStrBrk(previousNode,currentNode,previousLetter);
    			newNode = createNode();
    			newNode->lnkdStr = linkedStrAppnd(word,i,lastLetterIndex);
                newNode->endOfWord = true;
    			currentNode->children[charIndex] = newNode;
    			break;
    		}else
            {
                previousLetter = newData;
    			newData = newData->next;
    		}
    	    }
        }
    	i++;
    }
}
//function to search given node
TrieNode* searchNodes(TrieNode* rootNode,char* word)
{
    int lastIndex = strlen(word);
    int i=0;
    int charIndex;
    int pos=1;
    TrieNode* currentNode = rootNode;
    lnkdStr* newData = currentNode->lnkdStr;

    while(i<lastIndex)
    {
    	charIndex = calcCharIndex(word[i]);
    	if(newData == NULL && pos)
        {
            currentNode = currentNode->children[charIndex];
            if(currentNode != NULL){
    	       newData = currentNode->lnkdStr->next;
            }
            else{
               pos=0;
            }
    	}
        else if(pos && newData != NULL)
        {    
    	    newData = newData->next;
    	}
        i++;
    }

    while(newData != NULL)
    {
    	word[lastIndex] = newData->data;
    	newData = newData->next;
    	lastIndex++;
    }
    word[lastIndex] = '\0';

    return currentNode;
}
//function to store dictionary
TrieNode* storeDict(char* fileName)
{
    char word[MAX_WORD_SIZE];  //assume all the word are no more than MAX_WORD_SIZE characters
    FILE *fp = fopen(fileName,"r");
    if (fp == NULL)
    {
        printf("Error: File not found");
        exit(1);
    }
    TrieNode* rootNode = createNode();
    clock_t begin = clock();
    while(1)
    {
        fgets(word,MAX_WORD_SIZE,fp);
        insertNode(rootNode,word);
        if(feof(fp))        //tests the end-of-file indicator 
            break;
    }
    clock_t end = clock();
    double timeTaken = (double)(end-begin)/CLOCKS_PER_SEC;
    printf("Time taken to store dictionary: %.8lf s\n",timeTaken);
    fclose(fp);
    return rootNode;
}
//function to print suggested words
void printSuggetions(TrieNode* suggestedNode,char word_buffer[],int buffer_size)
{
    TrieNode* currentNode = suggestedNode;
    int i,j,newSize;

    if(currentNode->endOfWord)
    {
        for (j=0;j<buffer_size;j++)
        {
            printf("%c",word_buffer[j]);
        }
        printf("\n");
    }

    for (i=0;i<ALPHABET_SIZE;i++)
    {
        if(currentNode->children[i]!=NULL)
        {
            newSize = strToChr(currentNode->children[i]->lnkdStr,word_buffer,buffer_size);
            printSuggetions(currentNode->children[i],word_buffer,newSize+1);
        }
    }
}