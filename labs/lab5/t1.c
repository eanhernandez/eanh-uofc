#include <stdio.h>
#include <string.h>

int main(void) {

    int j, i=0; // used to iterate through array

    char userInput[81], *token[80]; //user input and array to hold max possible tokens, aka 80.

    printf("Enter a line of text to be tokenized: ");
    fgets(userInput, sizeof(userInput), stdin);

    token[0] = strtok(userInput, " "); //get pointer to first token found and store in 0
                                      //place in array
    while(token[i]!= NULL) {   //ensure a pointer was found
       i++;
       token[i] = strtok(NULL, " "); //continue to tokenize the string
    }
                                                                       
    for(j = 0; j <= i-1; j++) {
    printf("%s\n", token[j]); //print out all of the tokens
   }
   return 0; 
}

